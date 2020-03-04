#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;

int ch[MAXN][26],tot=1,fail[MAXN],rt = 1;
int ps[MAXN];

inline void insert(int i,char str[]){
    int len = strlen(str+1);int v = rt;
    FOR(i,1,len){
        int x = str[i]-'a';
        if(!ch[v][x]) ch[v][x] = ++tot;
        v = ch[v][x];
    }
    ps[i] = v;
}

inline void build(){
    std::queue<int> q;
    FOR(i,0,25){
        if(ch[rt][i]) fail[ch[rt][i]] = rt,q.push(ch[rt][i]);
        else ch[rt][i] = rt;
    }
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,0,25){
            if(ch[v][i]) fail[ch[v][i]] = ch[fail[v]][i],q.push(ch[v][i]);
            else ch[v][i] = ch[fail[v]][i];
        }
    }
}
int n;
int sm[MAXN];
char str[MAXN];

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

inline void dfs(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);sm[v] += sm[e[i].to];
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n){
        scanf("%s",str+1);
        insert(i,str);
    }
    build();
    scanf("%s",str+1);
    int v = rt,len = strlen(str+1);
    FOR(i,1,len){
        v = ch[v][str[i]-'a'];
        sm[v]++;
    }
    FOR(i,1,tot) add(fail[i],i);
    dfs(rt);
    FOR(i,1,n) printf("%d\n",sm[ps[i]]);
    return 0;
}

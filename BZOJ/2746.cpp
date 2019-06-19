#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;

int ch[MAXN][26],f[MAXN][21],fail[MAXN],dep[MAXN],val[MAXN],cnt = 1;
std::vector<int> p[MAXN];

inline void insert(char str[],int id){
    int v = 1,len = strlen(str+1);
    FOR(i,1,len){
        int x = str[i]-'a';
        if(!ch[v][x]) ch[v][x] = ++cnt;
        val[ch[v][x]] = (26ll*val[v]%ha+x)%ha;
        v = ch[v][x];p[id].pb(v);
    }
}

inline void build(){
    std::queue<int> q;q.push(1);
    FOR(i,0,25) ch[0][i] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,0,25){
            if(!ch[v][i]) ch[v][i] = ch[f[v][0]][i];
            else{
                f[ch[v][i]][0] = ch[f[v][0]][i];
                dep[ch[v][i]] = dep[f[ch[v][i]][0]]+1;
                q.push(ch[v][i]);
            }
        }
        FOR(i,1,19){
            f[v][i] = f[f[v][i-1]][i-1];
        }
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,19){
            if(d&(1<<i)) x = f[x][i];
        }
    }
    if(x == y) return x;
    ROF(i,19,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

char str[5000000];

int main(){
    int n;scanf("%d",&n);dep[1] = 1;
    FOR(i,1,n){
        scanf("%s",str+1);
        insert(str,i);
    }
    build();
    int q;scanf("%d",&q);
    while(q--){
        int x,y,a,b;scanf("%d%d%d%d",&x,&y,&a,&b);
        printf("%d\n",val[lca(p[x][y-1],p[a][b-1])]);
    }
    return 0;
}

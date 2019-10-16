/*
 * Author: RainAir
 * Time: 2019-10-12 08:44:47
 */
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;
const int MAXM = 2000+5;

struct Edge{
    int to,nxt;
}e[MAXM<<1];
int cnt,head[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;
int dfn[MAXN],low[MAXN],col[MAXN];
int stk[MAXN],tp,tot;
bool ins[MAXN];
char a[23],b[23];

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;ins[v] = true;stk[++tp] = v;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = stk[tp--];
            ins[t] = false;col[t] = tot;
        }while(t != v);
    }
}

inline void clear(){
    FOR(i,0,2*n) col[i] = ins[i] = head[i] = dfn[i] = low[i] = 0;cnt = tot = 0;
}

inline void Solve(){
    // m = 0,h = 1
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        scanf("%s%s",a+1,b+1);
        int ta = a[1]=='h',tb = b[1] == 'h';
        int len = strlen(a+1);int u = 0,v = 0;
        FOR(i,2,len) u = u*10+a[i]-'0';
        len = strlen(b+1);
        FOR(i,2,len) v = v*10+b[i]-'0';
        add(u+n*(!ta),v+n*tb);add(v+n*(!tb),u+n*ta);
    }
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    FOR(i,1,n) if(col[i] == col[n+i]){
        puts("BAD");
        clear();
        return;
    }
    puts("GOOD");
    clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

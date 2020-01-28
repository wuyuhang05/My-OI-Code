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

const int MAXN = 1e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int son[MAXN],dep[MAXN],len[MAXN];

inline void dfs1(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        dfs1(e[i].to,v);
        son[v] = len[son[v]] < len[e[i].to] ? e[i].to : son[v];
    }
    len[v] = len[son[v]] + 1;
}

LL *f[MAXN],*g[MAXN];
LL pool[MAXN<<2],*tail = pool;
LL ans;
int n;

inline void dfs2(int v,int fa=0){
    if(son[v]){
        f[son[v]] = f[v]+1;
        g[son[v]] = g[v]-1;
        dfs2(son[v],v);
    }
    f[v][0] = 1;ans += g[v][0];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || e[i].to == son[v]) continue;
        f[e[i].to] = tail;tail += len[e[i].to]<<1;
        g[e[i].to] = tail;tail += len[e[i].to]<<1;
        dfs2(e[i].to,v);
        FOR(j,0,len[e[i].to]){
            if(j+1 <= len[e[i].to]-1) ans += f[v][j]*g[e[i].to][j+1];
            if(j) ans += f[e[i].to][j-1]*g[v][j];
        }
        FOR(j,0,len[e[i].to]){
            if(j) g[v][j] += f[v][j]*f[e[i].to][j-1];
            if(j+1 <= len[e[i].to]-1) g[v][j] += g[e[i].to][j+1];
            if(j) f[v][j] += f[e[i].to][j-1];
        }
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs1(1);
    f[1] = tail;tail += len[1]<<1;
    g[1] = tail;tail += len[1]<<1;
    dfs2(1);
    printf("%lld\n",ans);
    return 0;
}
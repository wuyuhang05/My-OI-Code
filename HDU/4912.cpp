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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
std::vector<int> G[MAXN];
int n,m,dep[MAXN],f[MAXN][20];

struct Query{
    int u,v,l;

    bool operator < (const Query &other) const {
        return dep[l] > dep[other.l];
    }
}q[MAXN];

inline void dfs(int v){
    FOR(i,1,19) f[v][i] = f[f[v][i-1]][i-1];
    for(auto x:G[v]){
        if(x == f[v][0]) continue;
        f[x][0] = v;dep[x] = dep[v] + 1;
        dfs(x);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,19) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return y;
    ROF(i,19,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

bool vis[MAXN];

inline void tag(int v){
    vis[v] = true;
    for(auto x:G[v]){
        if(x == f[v][0]) continue;
        if(vis[x]) continue;
        tag(x);
    }
}

inline void Solve(){
    CLR(dep,0);CLR(f,0);CLR(vis,0);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dep[1] = 1;dfs(1);
    FOR(i,1,m){
        scanf("%d%d",&q[i].u,&q[i].v);
        q[i].l = lca(q[i].u,q[i].v);
    }
    std::sort(q+1,q+m+1);int ans = 0;
    FOR(i,1,m){
        if(!vis[q[i].u] && !vis[q[i].v]) ans++,tag(q[i].l);
    }
    printf("%d\n",ans);
    FOR(i,1,n) G[i].clear();
}

int main(){
    while(~scanf("%d%d",&n,&m)) Solve();
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-07-25 16:25:27
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

const int MAXN = 500000+5;
int g[MAXN],c[MAXN],dep[MAXN],f[21][MAXN],pa[MAXN];
int n,m,k,cnt;
std::vector<int> G[MAXN];
std::vector<P> mag[MAXN];

inline int find(int x){
    return x == pa[x] ? x : pa[x] = find(pa[x]);
}

inline void merge(int u,int v){
    int fu = find(u),fv = find(v);
    if(fu == fv) return;
    G[++cnt].pb(fu);G[fu].pb(cnt);
    G[cnt].pb(fv);G[fv].pb(cnt);
    pa[fu] = pa[fv] = cnt;
}

inline void dfs(int v,int fa=0){
    FOR(i,1,20){
        f[i][v] = f[i-1][f[i-1][v]];
    }
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(x == fa) continue;
        dep[x] = dep[v] + 1;
        f[0][x] = v;
        dfs(x,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,20){
            if(d&(1<<i)) x = f[i][x];
        }
    }
    if(x == y) return x;
    ROF(i,20,0){
        if(f[i][x] == f[i][y]) continue;
        x = f[i][x],y = f[i][y];
    }
    return f[0][x];
}

int main(){
    scanf("%d%d%d",&n,&m,&k);cnt = n;
    FOR(i,1,n) scanf("%d",g+i);
    FOR(i,1,2*n) pa[i] = i;
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        merge(u,v);
    }
    FOR(i,1,cnt){
        int t = find(i);
        if(!dep[t]){
            dep[t] = 1;dfs(t,0);
        }
    }
    FOR(i,1,k){
        int u,v;scanf("%d%d",&u,&v);
        int l = lca(u,v);mag[l].pb(MP(u,v));
    }
    LL ans = 0;
    FOR(i,n+1,cnt){
        FOR(j,0,(int)mag[i].size()-1){
            P x = mag[i][j];
            int t = std::min(g[x.fi],g[x.se]);
            g[x.fi] -= t;g[x.se] -= t;
            ans += t*2;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

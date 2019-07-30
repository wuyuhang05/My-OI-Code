/*
 * Author: RainAir
 * Time: 2019-07-26 15:20:25
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e6 + 5;
std::vector<int> G[MAXN];

struct Edge{
    int u,v,w;

    bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXN];
int n;
int p[MAXN],v[MAXN],f[MAXN],sm[MAXN],sz[MAXN],val[MAXN],cnt;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x,int y){
    int fx = find(x),fy = find(y);
    G[++cnt].pb(fx);G[cnt].pb(fy);
    G[fx].pb(cnt);G[fy].pb(cnt);
    f[fx] = f[fy] = cnt;
    sz[cnt] = sz[fx]+sz[fy];
}

int ans[MAXN];

inline void dfs(int v,int fa=0,int sum=0){
    sum += sm[v];ans[v] = sum;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs(x,v,sum);
    }
}

signed main(){
    scanf("%lld",&n);cnt = n;
    FOR(i,2,n) scanf("%lld",p+i);
    FOR(i,1,n) scanf("%lld",val+i);
    std::fill(sz,sz+n+1,1);
    FOR(i,2,n) e[i-1] = (Edge){i,p[i],std::max(val[p[i]],val[i])};
    std::sort(e+1,e+n);FOR(i,1,2*n) f[i] = i;
    FOR(i,1,n-1){
        int u = e[i].u,v = e[i].v,w = e[i].w;
        int fu = find(u),fv = find(v);
        sm[fu] += sz[fv]*w;sm[fv] += sz[fu]*w;
        merge(fu,fv);
    }
    int rt = find(1);
    dfs(rt);
    FOR(i,1,n) printf("%lld ",ans[i]+val[i]);puts("");
    return 0;
}


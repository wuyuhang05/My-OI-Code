/*
 * Author: RainAir
 * Time: 2019-08-29 11:12:17
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
#define int LL
const int MAXN = 2e5 + 5;

int f[MAXN],sz[MAXN],val[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

int n;

struct Edge{
    int u,v,w;

    bool operator < (const Edge &t) const {
        return w > t.w;
    }
}e[MAXN];

inline void Solve(){
    FOR(i,1,n) f[i] = i,sz[i] = 1,val[i] = 0;
    FOR(i,1,n-1) scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w);
    std::sort(e+1,e+n);
    int ans = 0;
    FOR(i,1,n-1){
        int u = find(e[i].u),v = find(e[i].v);
        if(u == v) continue; // Impossible
        int gx1 = sz[v]*e[i].w+val[u];
        int gx2 = sz[u]*e[i].w+val[v];
        ans = std::max(gx1,gx2);
        if(gx1 > gx2){
            f[v] = u;
            val[u] = gx1;
            sz[u] += sz[v];
        }
        else{
            f[u] = v;
            val[v] = gx2;
            sz[v] += sz[u];
        }
    }
    printf("%lld\n",ans);
}

signed main(){
    while(~scanf("%lld",&n)) Solve();
    return 0;
}

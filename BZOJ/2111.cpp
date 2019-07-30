/*
 * Author: RainAir
 * Time: 2019-07-20 13:59:33
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
int sz[MAXN],n,p;
int fac[MAXN],inv[MAXN],ha;
int ans = 1;
int lim = MAXN-5;
struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,lim) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[lim] = qpow(fac[lim]);
    ROF(i,lim-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int lucas(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    if(n < p && m < p) return C(n,m);
    return lucas(n/p,m/p)*lucas(n%p,m%p)%p;
}
int f[MAXN];

inline void dfs(int v,int fa=0){
    sz[v] = 1;int sl = -1,sr = -1;
    int &ans = f[v];ans = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);sz[v] += sz[e[i].to];
        ans = 1ll*ans*f[e[i].to]%ha;
        if(sl == -1) sl = sz[e[i].to];
        else sr = sz[e[i].to];
    }
    if(sl != -1) ans = 1ll*ans*lucas(sz[v]-1,sl)%ha;
}

signed main(){
    scanf("%lld%lld",&n,&p);ha = p;
    lim = std::min(lim,p-1);
    prework();
    ROF(i,n,1){
        if((i >> 1) > 0) add(i,i>>1);
    }
    dfs(1);
    printf("%lld\n",f[1]);
    return 0;
}

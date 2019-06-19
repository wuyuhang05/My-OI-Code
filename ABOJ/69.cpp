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
#define int LL
const int ha = 998244353;
const int MAXN = 200000+5;

inline int qpow(int a,LL n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int fac[MAXN],inv[MAXN];

inline void pre(){
    fac[0] = inv[0] = 1;
    FOR(i,1,200000) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[200000] = qpow(fac[200000]);
    ROF(i,199999,1) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

LL n,m,u,v;

inline void Solve(){
    scanf("%lld%lld%lld%lld",&n,&m,&u,&v);
    u %= ha;v %= ha;
    int ans = 0;
    FOR(i,0,m-1){
        int t = 1ll*fac[m-1]*inv[i]%ha*inv[m-1-i]%ha;
        if(i & 1) t = 1ll*t*(ha-1)%ha;
        int tt = ((1ll*u*m%ha-1ll*u*i%ha+v)%ha+ha)%ha;
        ans = (ans + 1ll*t*qpow(tt,n+m-1)%ha)%ha;
    }
    ans = 1ll*ans*qpow(u,ha-m)%ha*inv[m-1]%ha;
    printf("%lld\n",ans);
}

signed main(){
    pre();
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

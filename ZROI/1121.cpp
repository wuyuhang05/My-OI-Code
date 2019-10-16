/*
 * Author: RainAir
 * Time: 2019-10-01 16:45:13
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
#define LL long long
#define pb push_back
#define BLL __int128_t
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define P std::pair<BLL,std::pair<int,int> >
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 100+5;
const int ha = 998244353;
int n,x,y,z,a[MAXN],lim[MAXN],N;
int fac[MAXN],inv[MAXN];
std::vector<P> G;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline BLL _C(int n,int m){
    if(n < m) return 0;
    BLL ans = 1;
    FOR(i,n-m+1,n) ans = ans*i;
    FOR(i,2,m) ans /= i;
    return ans;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline void prob(int col,int a,int b){
    BLL res = 0;
    FOR(i,0,std::min(y,b-z)) res += _C(a-b,i)*_C(N-(a-b)-x,y-i);
    G.pb(MP(res,MP(col,b)));
}

inline int prob(int a,int b){
    int res = 0;
    FOR(i,0,std::min(y,b-z)) (res += C(a-b,i)*C(N-(a-b)-x,y-i)%ha)%=ha;
    return res;
}

int f[MAXN][MAXN];

inline int calc(int p,int s){
    CLR(f,0);f[0][0] = 1;
    FOR(i,1,n){
        if(i == p) FOR(j,0,s) f[i][j] = f[i-1][j];
        else{
            FOR(j,0,lim[i]) FOR(k,0,std::max(0ll,s-j)){
                (f[i][j+k] += f[i-1][k]*C(a[i],j)%ha) %= ha;
            }
        }
    }
    return f[n][s];
}

signed main(){
    prework();
    scanf("%lld%lld%lld%lld",&n,&x,&y,&z);
    FOR(i,1,n) scanf("%lld",a+i),N += a[i];
    FOR(i,1,n){
        FOR(j,z,std::min(x,a[i])){ // 第 i 个 颜色用了 j 个的 prob
            prob(i,a[i],j);
        }
    }
    std::sort(all(G));
    int ans = 0;
    FOR(i,1,n) lim[i] = std::min(a[i],z-1);
    for(auto x:G)
        (ans += calc(x.se.fi,::x-x.se.se)*prob(a[x.se.fi],x.se.se)%ha*C(a[x.se.fi],x.se.se)%ha) %= ha,
        lim[x.se.fi] = x.se.se;
    printf("%lld\n",ans*qpow(C(N-x,y)*C(N,x)%ha)%ha);
    return 0;
}

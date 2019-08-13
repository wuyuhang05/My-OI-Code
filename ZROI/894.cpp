/*
 * Author: RainAir
 * Time: 2019-08-10 19:40:17
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
const int MAXN = 1e5 + 5;
int n,ha;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int fac[MAXN],inv[MAXN];

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int ans = 0;

signed main(){
    scanf("%lld%lld",&n,&ha);prework();
    FOR(d,1,n-1){
        FOR(x,2,n){
            if(d*(x-1) >= n) break;
            int p = n-(x-1)*(d-1),q = x-1;
            int mn = (C(p+1,q+1)*(p+1)%ha-(q+1)*C(p+2,q+2)%ha+ha)%ha;
            int all = C(p,q+1)*(n+1)%ha;
            int mx = (all-mn+ha)%ha;
            int gx = (mx-mn+ha)%ha;
            (ans += gx) %= ha;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-07-20 13:48:09
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
const int MAXN = 3e5 + 5;
const int ha = 998244353;
int n,a,b,k;
int fac[MAXN],inv[MAXN];

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

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int ans = 0;

signed main(){
    prework();
    scanf("%lld%lld%lld%lld",&n,&a,&b,&k);
    FOR(x,0,n){
        int t = k-a*x;if(t < 0) break;
        if(t%b) continue;
        int y = t/b;//DEBUG(x);DEBUG(y);
        if(y > n) continue;
        (ans += C(n,x)*C(n,y)%ha) %= ha;
    }
    printf("%lld\n",ans);
    return 0;
}

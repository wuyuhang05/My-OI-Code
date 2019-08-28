/*
 * Author: RainAir
 * Time: 2019-08-27 19:22:27
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
const int ha = 1e9 + 7;
const int MAXN = 1e6 + 5;

inline int qpow(int a,int n=ha-2){
    if(a < 0) return 0;
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int cs,n,m,k,f[MAXN];// (m,*)

inline void prepare(){
    f[0] = 1;f[1] = k;
    FOR(i,2,k) f[i] = 1ll*f[i-1]*(k-i+1)%ha*qpow(i)%ha;
    f[k] = 1;
}

int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    int ans = 1,t = 1;
    FOR(i,n-m+1,n) ans = 1ll*ans*(i%ha)%ha;
    FOR(i,1,m) t = 1ll*t*i%ha;
    return 1ll*ans*qpow(t)%ha;
}

inline void Solve(){
    printf("Case #%lld: ",++cs);
    scanf("%lld%lld%lld",&n,&m,&k);
    prepare();int ans = 0;
    FOR(i,1,k){
        ans = (ans + ((f[i]*i%ha*qpow(i-1,n-1)%ha)*((k-i)&1 ? -1 : 1)) + ha)%ha;
    }
    printf("%lld\n",ans*C(m,k)%ha);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

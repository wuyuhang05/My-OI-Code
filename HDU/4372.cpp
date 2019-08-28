/*
 * Author: RainAir
 * Time: 2019-08-26 16:25:22
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

const int MAXN = 2000+5;
const int ha = 1e9 + 7;

int fac[MAXN],inv[MAXN],S[MAXN][MAXN];

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
    S[0][0] = 1;
    FOR(i,1,MAXN-1){
        S[i][0] = 0;
        FOR(j,1,i) S[i][j] = ((i-1)*S[i-1][j]%ha+S[i-1][j-1]%ha)%ha;
    }
}

inline int C(int n,int m){
    if(n < m) return 0;
    return fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline void Solve(){
    int n,f,b;scanf("%lld%lld%lld",&n,&f,&b);
    int t = f+b-2;
    if(t > 2000){
        puts("0");return;
    }
    printf("%lld\n",C(t,f-1)*S[n-1][t]%ha);
}

signed main(){
    prework();
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

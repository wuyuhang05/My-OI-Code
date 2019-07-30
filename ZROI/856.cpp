/*
 * Author: RainAir
 * Time: 2019-07-26 16:04:47
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
const int MAXN = 1000+5;
const int ha = 998244353;
int f[MAXN][MAXN];
int n,a[MAXN];
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

inline void init(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

signed main(){
    init();
    scanf("%lld",&n);FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,2,n){
        if(a[i] == a[i-1]){
            puts("0");return 0;
        }
    }
    FOR(i,1,n) f[i][i] = 1;
    FOR(i,1,n+1) f[i][i-1] = 1;
    a[0] = a[n+1] = -1;
    FOR(len,2,n){
        FOR(l,1,n){
            int r = l+len-1;
            if(r > n) break;
            FOR(k,l,r){
                if(a[k] != a[l-1] && a[k] != a[r+1])
                    (f[l][r] += 1ll*f[l][k-1]*f[k+1][r]%ha*C(r-l,k-l)) %= ha;
            }
        }
    }
    printf("%lld\n",f[1][n]);
    return 0;
}

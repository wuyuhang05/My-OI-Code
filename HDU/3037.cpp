/*
 * Author: RainAir
 * Time: 2019-08-26 17:26:41
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

const int MAXN = 2e5 + 5;
int fac[MAXN],inv[MAXN],p;

inline int qpow(int a,int n=p-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%p;
        a = 1ll*a*a%p;
        n >>= 1;
    }
    return res;
}

inline void prework(int n){
    fac[0] = 1;FOR(i,1,n) fac[i] = 1ll*fac[i-1]*i%p;
    inv[n] = qpow(fac[n]);
    ROF(i,n-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%p;
}

inline int calc(int n,int m){
    int res = 1,b = 1;
    ROF(i,n,n-m+1) res = 1ll*res*i%p;
    FOR(i,1,m) b = 1ll*i*b%p;
    return 1ll*res*qpow(b)%p;
}

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    if(n < p && m < p) return calc(n,m);
    return 1ll*C(n/p,m/p)*C(n%p,m%p)%p;
}

inline void Solve(){
    int n,m;scanf("%d%d%d",&n,&m,&p);//prework(p-1);
    printf("%d\n",C(n+m,m));
}

signed main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

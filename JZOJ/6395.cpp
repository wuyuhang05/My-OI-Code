/*
 * Author: RainAir
 * Time: 2019-11-01 21:53:24
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

const int MAXN = 4e6 + 5;
const int ha = 1e9 + 7;
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

inline int F(int n,int m){
    if(n < m) return 0;
    if(n < 0 || m < 0) return 0;
    return (C(n+m,n)+ha-C(n+m,n+1))%ha;
}

int ans = 0;
int n,ps,x;

int main(){
    freopen("stack.in","r",stdin);
    freopen("stack.out","w",stdout);
    scanf("%d%d%d",&n,&ps,&x);
    prework();
    FOR(l,1,2*n){
        (ans += 1ll*F(ps-1,l-ps)*F(ps+x-l-1,ps+x-l-1)%ha*F(n-x,n-2*ps-x+l+1)%ha) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}

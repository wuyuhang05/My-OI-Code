/*
 * Author: RainAir
 * Time: 2019-07-20 18:50:21
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

const int MAXN = 5000+5;
const int ha = 998244353;
#define int LL
inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int fac[MAXN],inv[MAXN],n,num[5];

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

int poly[5][MAXN],len[5],pos[MAXN];

inline void NTT(int *A,int lim,int opt){
    FOR(i,0,lim-1) if(i < pos[i]) std::swap(A[i],A[pos[i]]);
    for(int mid = 1;mid < lim;mid <<= 1){
        int W = qpow(3,(ha-1)/(mid<<1));
        if(opt == -1) W = qpow(W);
        for(int j = 0;j < lim;j += (mid << 1)){
            for(int k = 0,w = 1;k < mid;++k,w = 1ll*w*W%ha){
                int x = A[j+k],y = w*A[j+mid+k]%ha;
                A[j+k] = (x+y)%ha;A[j+mid+k] = (x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(lim,ha-2);
        FOR(i,0,lim-1) A[i] = 1ll*A[i]*inv%ha;
    }
}
int t[5];
inline int calc(int k){
    int lim = 1,len = 0;
 //   while(lim <= std::max((num[4]-k)<<1,(n-4*k)<<1)) lim <<= 1,len++;
    while(lim <= num[4]*4) lim <<= 1,len++;
    FOR(i,1,lim-1) pos[i] = (pos[i>>1]>>1|((i&1)<<(len-1)));
    FOR(i,1,4){
        t[i] = num[i]-k;
        FOR(j,0,lim) poly[i][j] = 0;
    }
    FOR(i,1,4) FOR(j,0,t[i]) poly[i][j] = inv[j];
    FOR(i,1,4) NTT(poly[i],lim,1);
    FOR(i,2,4) FOR(j,0,lim-1) poly[1][j] = 1ll*poly[1][j]*poly[i][j]%ha;
    NTT(poly[1],lim,-1);
    return 1ll*poly[1][n-4*k]*fac[n-4*k]%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}
int ans = 0;
signed main(){
    prework();
    scanf("%lld",&n);FOR(i,1,4) scanf("%lld",num+i);
    std::sort(num+1,num+5);
    for(int i = 0;(i << 2) <= std::min(n,num[1]<<2);++i){
        int t = 1ll*calc(i)*C(n-3*i,i)%ha;
        if(i & 1) ans = (ans-t+ha)%ha;
        else ans = (ans+t)%ha;
    }
    printf("%lld\n",ans);
    return 0;
}

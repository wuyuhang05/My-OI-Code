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

const int MAXN = 6000+5;
const int ha = 998244353;
int n,num[MAXN];

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int len[5],fac[MAXN],inv[MAXN],rev[MAXN];
int poly[5][MAXN],C[MAXN][MAXN];

inline void init(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1],ha-2);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline void NTT(int *A,int limit,int opt){
    for(int i = 0,k = 0;i < limit;++i){
        if(i > k) std::swap(A[i],A[k]);
        for(int j = limit>>1;(k^=j)<j;j>>=1);
    }
    for(int mid = 1;mid < limit;mid <<= 1){
        int W = qpow(3,(ha-1)/(mid<<1));
        if(opt == -1) W = qpow(W,ha-2);
        for(int j = 0;j < limit;j += (mid<<1)){
            for(int k = 0,w = 1;k < mid;++k,w = 1ll*w*W%ha){
                LL x = A[j+k],y = 1ll*w*A[j+mid+k]%ha;
                A[j+k] = (1ll*x+y)%ha;A[j+mid+k] = (1ll*x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(limit,ha-2);
        FOR(i,0,limit-1) A[i] = 1ll*A[i]*inv%ha;
    }
}

inline int calc(int k){
    int limit = 1;
    while(limit <= std::max((num[4]-k)<<1,(n-4*k)<<1)) limit <<= 1;
    while(limit <= (num[4] << 2)) limit <<= 1;
    FOR(i,1,4){
        len[i] = num[i] - k;
        FOR(j,0,limit) poly[i][j] = 0;
    }
    FOR(i,1,4) FOR(j,0,len[i]) poly[i][j] = inv[j];
    FOR(i,1,4) NTT(poly[i],limit,1);
    FOR(i,2,4){
        FOR(j,0,limit-1) poly[1][j] = 1ll*poly[1][j]*poly[i][j]%ha;
    }
    NTT(poly[1],limit,-1);
    return 1ll*poly[1][n-4*k]*fac[n-4*k]%ha;
}

int main(){
    scanf("%d",&n);FOR(i,1,4) scanf("%d",num+i);
    FOR(i,0,n){
        C[i][0] = 1;
        FOR(j,1,i) C[i][j] = (C[i-1][j]+C[i-1][j-1])%ha;
    }
    std::sort(num+1,num+5);
    int limit = 1;while(limit <= (num[4]<<2)) limit <<= 1;
    init();int ans = 0;
    for(int i = 0;(i<<2)<=std::min(n,num[1]<<2);++i){
        int t = 1ll*calc(i)*C[n-3*i][i]%ha;
        if(i & 1) ans = (ans - t + ha)%ha;
        else ans = (ans + t)%ha;
    }
    printf("%d\n",ans);
    return 0;
}

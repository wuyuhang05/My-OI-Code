/*
 * Author: RainAir
 * Time: 2019-07-31 20:08:08
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
const int ha = 998244353;
const int g = 3;
const int MAXN = 3e5 + 5;
int n;
char str[MAXN];
int a[MAXN],b[MAXN],f[MAXN],inv[MAXN],fac[MAXN];

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
    f[0] = fac[0] = a[0] = b[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

int A[MAXN],B[MAXN],rev[MAXN];

inline void NTT(int *A,int lim,int opt){
    FOR(i,0,lim-1) if(i < rev[i]) std::swap(A[i],A[rev[i]]);
    for(int mid = 1;mid < lim;mid <<= 1){
        int W = qpow(g,(ha-1)/(mid<<1));
        for(int i = 0;i < lim;i += (mid << 1)){
            for(int w = 1,j = 0;j < mid;++j,w = 1ll*w*W%ha){
                int x = A[i+j],y = w*A[i+mid+j]%ha;
                A[i+j] = (x+y)%ha;A[i+mid+j] = (x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        std::reverse(A+1,A+lim);
        int inv = qpow(lim);
        FOR(i,0,lim-1) A[i] = A[i]*inv%ha;
    }
}

inline void mul(int *A,int *B,int lena,int lenb){
    int lim = 1,len = 0;
    while(lim <= (lena+lenb)) lim <<= 1,len++;
    FOR(i,1,lim-1) rev[i] = (rev[i>>1]>>1)|((i&1)<<(len-1));
    FOR(i,lena+1,lim) A[i] = 0;
    FOR(i,lenb+1,lim) B[i] = 0;
    NTT(A,lim,1);NTT(B,lim,1);
   //     FOR(i,0,lena) printf("%d ",A[i]);puts("");
   // FOR(i,0,lenb)printf("%d ",B[i]);puts("");

    FOR(i,0,lim-1) A[i] = 1ll*A[i]*B[i]%ha;
//        printf("%d ",A[i]);
    NTT(A,lim,-1);
 //   exit(0);
}

inline void solve(int l,int r){
    if(l == r){
        f[l] = 1ll*f[l]*b[l]%ha;
        return;
    }
    int mid = (l + r) >> 1;
    solve(l,mid);//CLR(A,0);CLR(B,0);
    FOR(i,l,mid) A[i-l] = a[i]*f[i]%ha;
    FOR(i,l,r) B[i-l] = inv[i-l];
    mul(A,B,mid-l,r-l);
    FOR(i,mid+1,r) f[i] = (f[i]+A[i-l])%ha;
    solve(mid+1,r);
}

signed main(){
    scanf("%s",str+1);n = strlen(str+1);
    init();n++;
    FOR(i,1,n){
        b[i] = a[i-1];
        a[i] = (str[i] != '<') ? (ha-a[i-1]) : (a[i-1]);
    }
    FOR(i,1,n-1) if(str[i] == '<') a[i] = 0;
  //  FOR(i,0,n) printf("%d ",a[i]);puts("");
    solve(0,n);//DEBUG(f[n]);
    printf("%lld\n",f[n]*fac[n]%ha);
    return 0;
}

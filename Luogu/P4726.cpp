#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5e5 + 5;
const int ha = 998244353;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = res*a%ha;
        a = a*a%ha;
        n >>= 1;
    }
    return res;
}

int a[MAXN],b[MAXN],c[MAXN],d[MAXN],r[MAXN],g[MAXN],f[MAXN],x[MAXN],n;

inline void NTT(int *A,int limit,int opt){
    FOR(i,0,limit-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
    for(int mid = 1;mid < limit;mid <<= 1){
        int W = qpow(3,(ha-1)/(mid<<1));
        if(opt == -1) W = qpow(W,ha-2);
        for(int j = 0;j < limit;j += (mid<<1)){
            for(int k = 0,w = 1;k < mid;k++,w = w*W%ha){
                int x = A[j+k],y = w*A[j+mid+k]%ha;
                A[j+k] = (x+y)%ha;A[j+mid+k] = (x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(limit,ha-2);
        FOR(i,0,limit-1) A[i] = A[i]*inv%ha;
    }
}

inline void Inv(int *A,int *B,int n){
    B[0] = qpow(A[0],ha-2);
    int len;
    for(len = 1;len < (n<<1);len <<= 1){
        int d = len<<1;
        FOR(i,0,len-1) a[i] = A[i],b[i] = B[i];
        FOR(i,0,d-1) r[i] = (r[i>>1]>>1)|((i&1)?len:0);
        NTT(a,d,1);NTT(b,d,1);
        FOR(i,0,d-1) B[i] = (2-a[i]*b[i]%ha+ha)%ha*b[i]%ha;
        NTT(B,d,-1);FOR(i,len,d-1) B[i] = 0;
    }
    FOR(i,0,len-1) a[i] = b[i] = 0;
    FOR(i,n,len-1) B[i] = 0;
}

inline void Direv(int *A,int *B,int n){
    FOR(i,1,n-1) B[i-1] = i*A[i]%ha;B[n-1] = 0;
}

inline void Inter(int *A,int *B,int n){
    FOR(i,1,n-1) B[i] = A[i-1]*qpow(i,ha-2)%ha;B[0] = 0;
}

inline void getln(int *A,int *B,int n){
    int *C = c,*D = d;
    Direv(A,C,n);Inv(A,D,n);
    int len = 0,limit = 1;
    while(limit <= n) limit <<= 1,len++;
    FOR(i,1,limit-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
    NTT(C,limit,1);NTT(D,limit,1);
    FOR(i,0,limit-1) C[i] = C[i]*D[i]%ha;
    NTT(C,limit,-1);Inter(C,B,n);
}

inline void Exp(int *A,int *B,int n){
    B[0] = 1;int len;
    for(len = 1;len < (n<<1);len <<= 1){
        int d = len<<1;
        getln(B,f,len);
        FOR(i,0,len-1) f[i] = (A[i]+(i==0)-f[i]+ha)%ha;
        FOR(i,0,d-1) r[i] = (r[i>>1]>>1)|((i&1)?len:0);
        NTT(B,d,1);NTT(f,d,1);
        FOR(i,0,d-1) B[i] = B[i]*f[i]%ha;
        NTT(B,d,-1);
        FOR(i,len,d-1) B[i] = 0;
    }
    FOR(i,0,len-1) f[i] = 0;FOR(i,n,len-1) B[i] = 0;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,0,n-1) scanf("%lld",x+i);
    int len;for(len=1;len<=n;len<<=1);Exp(x,g,len);
    FOR(i,0,n-1) printf("%lld ",g[i]);
    return 0;
}
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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 400000+5;
const int ha = 998244353;
const int inv = 499122177;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = (res*a) % ha;
        a = (a*a)%ha;
        n >>= 1;
    }
    return res;
}

int pos[MAXN],a[MAXN],b[MAXN],c[MAXN],d[MAXN],f[MAXN],g[MAXN],n;

inline void NTT(int *A,int limit,int opt){
    FOR(i,0,limit-1) if(i < pos[i]) std::swap(A[i],A[pos[i]]);
    for(int mid = 1;mid < limit;mid <<= 1){
        int W = qpow(3,(ha-1)/(mid<<1));
        if(opt == -1) W = qpow(W,ha-2);
        for(int i = 0;i < limit;i += (mid<<1)){
            for(int w = 1,j = 0;j < mid;++j,w = w*W%ha){
                int x = A[i+j],y = w*A[i+mid+j]%ha;
                A[i+j] = (x+y)%ha;A[i+mid+j] = (x-y+ha)%ha;
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
        FOR(i,0,d-1) pos[i] = (pos[i>>1]>>1)|((i&1)?len:0);
        NTT(a,d,1);NTT(b,d,1);
        FOR(i,0,d-1) B[i] = ((2-a[i]*b[i]%ha+ha)%ha*b[i]%ha)%ha;
        NTT(B,d,-1);
        FOR(i,len,d-1) B[i] = 0;
    }
    FOR(i,0,len-1) a[i] = b[i] = 0;
    FOR(i,n,len-1) B[i] = 0;
}

inline void Sqrt(int *A,int *B,int n){
    B[0] = 1;
    int *a = c,*b = d,len;
    for(len = 1;len < (n<<1);len<<=1){
        int d = len<<1;
        FOR(i,0,len-1) a[i] = A[i];
        Inv(B,b,d>>1);
        FOR(i,0,d-1) pos[i] = (pos[i>>1]>>1)|((i&1)?len:0);
        NTT(a,d,1);NTT(b,d,1);
        FOR(i,0,d-1) a[i] = a[i]*b[i]%ha;
        NTT(a,d,-1);
        FOR(i,0,len-1) B[i] = (B[i]+a[i])%ha*inv%ha;
        FOR(i,len,d-1) B[i] = 0;
    }
    FOR(i,0,len-1) a[i] = b[i] = 0;
    FOR(i,n,len-1) B[i] = 0;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,0,n-1) scanf("%lld",f+i);
    Sqrt(f,g,n);
    FOR(i,0,n-1) printf("%lld ",g[i]);
    puts("");
    return 0;
}
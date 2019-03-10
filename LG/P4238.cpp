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
const int ha = 998244353;
const int MAXN = 2100000+5;

int a[MAXN],b[MAXN],c[MAXN],pos[MAXN],n;

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = (res*a)%ha;
        a = (a*a)%ha;
        n >>= 1;
    }
    return res;
}

inline void NTT(int *A,int n,int opt){
    FOR(i,0,n-1) if(i < pos[i]) std::swap(A[i],A[pos[i]]);
    for(int mid = 1;mid < n;mid <<= 1){
        int W = qpow(3,(ha-1)/(mid<<1));
        for(int j = 0;j < n;j += (mid<<1)){
            for(int w = 1,k = 0;k < mid;k++,w = w*W%ha){
                int x = A[j+k],y = w*A[j+mid+ k]%ha;
                A[j+k] = (x+y)%ha;A[j+mid+k] = (x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(n,ha-2);std::reverse(A+1,A+n);
        FOR(i,0,n-1) A[i] = A[i]*inv%ha;
    }
}

inline void work(int *A,int *B,int mod){
    if(mod == 1){
        B[0] = qpow(A[0],ha-2);
        return;
    }
    work(A,B,(mod+1)>>1);
    int len = 0,limit = 1;
    while(limit < (mod<<1)) limit <<= 1,len++;
    FOR(i,1,limit-1) pos[i] = (pos[i>>1]>>1)|((i&1)<<(len-1));
    FOR(i,0,mod-1) c[i] = A[i];FOR(i,mod,limit-1) c[i] = 0;
    NTT(c,limit,1);NTT(B,limit,1);
    FOR(i,0,limit-1) B[i] = (2-B[i]*c[i]%ha+ha)%ha*B[i]%ha;
    NTT(B,limit,-1);
    FOR(i,mod,limit-1) B[i] = 0;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,0,n-1) scanf("%lld",a+i);
    work(a,b,n);
    FOR(i,0,n-1) printf("%lld ",b[i]);
    return 0;
}
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
const int MAXN = 300000+5;
const int ha = 998244353;

int A[MAXN],B[MAXN],f[MAXN],g[MAXN];

inline LL qpow(LL a,int n){
    LL res = 1ll;
    while(n){
        if(n & 1) res = (res*a)%ha;
        a = (a*a)%ha;
        n >>= 1;
    }
    return res;
}

int pos[MAXN],w[MAXN],l,n,limit;

// inline void init(int len){
//     limit = 1;l = 0;
//     while(limit < (len<<1)) limit <<= 1,l++;
//     FOR(i,0,limit-1) pos[i] = (pos[i>>1]>>1)|((i&1)<<(l-1));
// }

inline void init(int len){
    limit=1,l=0;
    while(limit<len*2) limit<<=1,++l;
    for(int i=0;i<limit;++i)
    pos[i]=(pos[i>>1]>>1)|((i&1)<<(l-1));
}

// inline void NTT(int *A,int opt){
//     FOR(i,0,limit-1) if(i < pos[i]) std::swap(A[i],A[pos[i]]);
//     for(int mid = 1;mid < limit;mid <<= 1){
//         int W = qpow(3,(ha-1)/(mid<<1));w[0] = 1;
//         FOR(j,1,mid-1) w[j] = w[j-1]*W%ha;
//         for(int j = 0;j < limit;j += (mid<<1)){
//             FOR(k,0,mid-1){
//                 int x = A[j+k]%ha,y = w[k]*A[j+mid+k]%ha;
//                 A[j+k] = (x+y)%ha;A[j+mid+k] = (x-y+ha)%ha;
//             }
//         }
//     }
//     if(opt == -1){
//         std::reverse(A+1,A+limit);
//         for(int i = 0,inv = qpow(limit,ha-2);i < limit;++i) A[i] = A[i]*inv%ha;
//     }
// }

void NTT(int *A,int type){
    for(int i=0;i<limit;++i)
    if(i<pos[i]) std::swap(A[i],A[pos[i]]);
    for(int mid=1;mid<limit;mid<<=1){
        int R=mid<<1,Wn=qpow(3,(ha-1)/R);w[0]=1;
        for(int j=1;j<mid;++j) w[j]=(w[j-1]*Wn%ha);
        for(int j=0;j<limit;j+=R){
            for(int k=0;k<mid;++k){
                int x=A[j+k],y=(w[k]*A[j+k+mid]%ha);
                A[j+k]=(x+y)%ha,A[j+k+mid]=(x-y+ha)%ha;
            }
        }
    }
    if(type==-1){
        std::reverse(A+1,A+limit);
        for(int i=0,inv=qpow(limit,ha-2);i<limit;++i)
        A[i]=(A[i]*inv)%ha;
    }
}

inline void cdq(int *a,int *b,int l,int r){
    if(l == r) return;
    int mid = (l + r) >> 1;cdq(a,b,l,mid);
    init(r-l+1);
    FOR(i,0,limit-1) A[i] = B[i] = 0;
    FOR(i,l,mid) A[i-l] = a[i];
    FOR(i,0,r-l) B[i] = b[i];
    NTT(A,1);NTT(B,1);
    FOR(i,0,limit-1) A[i] = A[i]*B[i]%ha;
    NTT(A,-1);
    FOR(i,mid+1,r) a[i] = (a[i] + A[i-l])%ha;
    cdq(a,b,mid+1,r);
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n-1) scanf("%lld",g+i);f[0] = 1;
    cdq(f,g,0,n-1);
    FOR(i,0,n-1) printf("%lld ",f[i]);
    return 0;
}
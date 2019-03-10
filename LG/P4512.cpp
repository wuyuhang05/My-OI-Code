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

const int MAXN = 400000+5;
const int ha = 998244353;
const int G = 3;
const int Gi = 332748118;

inline char nc(){
    static char buf[MAXN],*p1 = buf,*p2 = buf+MAXN;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,MAXN,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    int res = 1;char ch = nc();int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = (1ll*res*a)%ha;
        a = (1ll*a*a)%ha;
        n >>= 1;
    }
    return res;
}

int limit,len,pos[MAXN];

inline void NTT(int *A,int opt){
    FOR(i,0,limit-1) if(i < pos[i]) std::swap(A[i],A[pos[i]]);
    for(int mid = 1;mid < limit;mid <<= 1){
        int W = qpow(opt==1?G:Gi,(ha-1)/(mid<<1));
        for(int j = 0;j < limit;j += (mid<<1)){
            for(int k = 0,w = 1;k < mid;++k,w = 1ll*w*W%ha){
                int x = A[j+k],y = 1ll*w*A[j+mid+k]%ha;
                A[j+k] = (x+y)%ha;A[j+mid+k] = (x-y+ha)%ha;
            }
        }
    }
    if(opt == -1){
        int inv = qpow(limit,ha-2);//std::reverse(A+1,A+limit);
        FOR(i,0,limit-1) A[i] = 1ll*A[i]*inv%ha;
    }
}

inline void init(int n){
    limit = 1,len = 0;
    while(limit < n) limit <<= 1,len++;
    FOR(i,0,limit-1) pos[i] = (pos[i>>1]>>1)|((i&1)<<(len-1));
}

int x[MAXN],y[MAXN],c[MAXN],f[MAXN],g[MAXN],inv[MAXN],n,m;

inline void mul(int *A,int *B,int *C,int N,int M){
    init(N+M);
    FOR(i,0,limit-1){
        x[i] = i<N ? A[i] : 0;
        y[i] = i<M ? B[i] : 0;
    }
    NTT(x,1);NTT(y,1);
    FOR(i,0,limit-1) C[i] = 1ll*x[i]*y[i]%ha;
    NTT(C,-1);
}

inline void getinv(int *A,int *B,int n){
    if(n == 1){
        B[0] = qpow(A[0],ha-2);
        return;
    }
    int d = (n+1)>>1;
    getinv(A,B,d);
    mul(A,B,c,m+1,d);
    c[0] = (2+ha-c[0])%ha;
    FOR(i,1,m+d) c[i] = (ha-c[i])%ha;
    mul(c,B,B,m+d+1,d);
    FOR(i,n,limit-1) B[i] = 0;
}

signed main(){
    read(n);read(m);
    FOR(i,0,n) read(f[i]);
    FOR(i,0,m) read(g[i]);
    std::reverse(f,f+n+1);std::reverse(g,g+m+1);
    getinv(g,inv,n-m+1);
    mul(f,inv,c,n+1,n-m+1);
    std::reverse(c,c+n-m+1);
    FOR(i,0,n-m) printf("%d ",c[i]);puts("");
    std::reverse(f,f+n+1);std::reverse(g,g+m+1);
    mul(g,c,c,m+1,n-m+1);
    FOR(i,0,m-1) printf("%d ",(f[i]-c[i]+ha)%ha);
    return 0;
}
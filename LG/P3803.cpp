#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;
#undef R

const int MAXN = 10000000 + 5;

const double PI = acos(-1.0);
struct complex{
    double x,y;
    complex(double x=0,double y=0) : x(x),y(y) {}
}a[MAXN],b[MAXN];

complex operator + (const complex &a,const complex &b){
    return complex(a.x + b.x,a.y + b.y);
}

complex operator - (const complex &a,const complex &b){
    return complex(a.x-b.x,a.y-b.y);
}

complex operator * (const complex &a,const complex &b){
    return complex(a.x * b.x - a.y * b.y,a.x*b.y+a.y*b.x);
}

int N,M;
int f[MAXN],g[MAXN],r[MAXN];
int limit=1,len;

void fft(complex *A,int opt){
    FOR(i,0,limit){
        if(i < r[i]) std::swap(A[i],A[r[i]]);
    }
    for(int mid = 1;mid < limit;mid <<= 1){
        complex W(cos(PI/mid),opt*sin(PI/mid));
        for(int j=0,R = (mid << 1);j < limit;j += R){
            complex w(1,0);
            for(int k = 0;k < mid;k++,w=w*W){
                complex x = A[j+k],t=w*A[j+mid+k];
                A[j+k] = x+t;
                A[j+mid+k] = x-t;
            }
        }
    }
}

int main(){
    read(N);read(M);
    FOR(i,0,N){
        int x;read(x);a[i].x = x;
    }
    FOR(i,0,M){
        int x;read(x);b[i].x = x;
    }
    while(limit <= N + M){
        limit <<= 1;len++;
    }
    FOR(i,0,limit){
        r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
    }
    fft(a,1);
    fft(b,1);
    FOR(i,0,limit) a[i] = a[i]*b[i];
    fft(a,-1);
    FOR(i,0,N+M) printf("%d%c",(int)(a[i].x/limit+0.5),(i == N + M) ? '\n': ' ');
    return 0;
}

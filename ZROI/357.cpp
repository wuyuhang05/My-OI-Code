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

const int MAXN = 100000 + 5;
int N,M;
int a[MAXN];
LL f[2][MAXN];

struct Queue{
    LL q[MAXN],num[MAXN];
    int head,tail;
    
    inline void init(){
        CLR(q,0);
        head = 0;tail = -1;
    }

    inline void push1(LL x,int pos){
        while(head <= tail && q[tail] >= x) tail--;
        q[++tail] = x;num[tail] = pos;
    }

    inline void push2(LL x,int pos){
        while(head <= tail && q[tail] <= x) tail--;
        q[++tail] = x;num[tail] = pos;
    }

    inline void pop(int pos){
        while(num[head] >= pos) head++;
    }

    inline LL calc(){
        return q[head];
    }
}q1,q2;


int main(){
    read(N);read(M);
    FOR(i,1,N) read(a[i]);
    FOR(i,1,N){
        f[0][i] = LLONG_MIN;
        f[1][i] = LLONG_MAX;
    }
    q1.init();q2.init();
    f[0][N] = f[1][N] = 0;
    // DEBUG(f[0][N]);DEBUG(f[1][N]);
    q1.push1(-a[N],N);q2.push2(a[N],N);
    ROF(i,N-1,0){
        f[0][i] = q2.calc();f[1][i] = q1.calc();
        q1.pop(i+M);q2.pop(i+M);
        q1.push1(f[0][i] - a[i],i);q2.push2(f[1][i] + a[i],i);
    }
    printf("%lld\n%lld\n",f[0][0],f[1][0]);
    return 0;
}
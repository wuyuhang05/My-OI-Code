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

const int MAXN = 1000000 + 5;

struct Queue{
    int q[MAXN],num[MAXN];
    int head,tail;

    inline void init(){
        CLR(q,0);
        head = 0;tail = -1;
    }

    inline void push1(int x,int pos){ // min
        while(head <= tail && q[tail] >= x) tail--;
        q[++tail] = x;num[tail] = pos;
    }

    inline void push2(int x,int pos){ // max
        while(head <= tail && q[tail] <= x) tail--;
        q[++tail] = x;num[tail] = pos;
    }

    inline void pop(int pos){
        while(num[head] <= pos) head++;
    }

    inline int calc(){
        return q[head];
    }

    inline void DE(){
        printf("head:%d,tail:%d\n",head,tail);
        FOR(i,head,tail) printf("%d ",q[i]);
        puts("");
    }
}q1,q2;

int N,K;
std::vector<int> ans1,ans2;

int main(){
    read(N);read(K);
    q1.init();q2.init();
    FOR(i,1,N){
        int x;read(x);
        q1.push1(x,i);
        q2.push2(x,i);
        q1.pop(i-K);
        q2.pop(i-K);
        //q1.DE();q2.DE();
        if(i >= K){
            ans1.push_back(q1.calc());
            ans2.push_back(q2.calc());
        }
    }
    int sz = ans1.size()-1;
    FOR(i,0,sz)
        printf("%d%c",ans1[i],(i == sz) ? '\n' : ' ');
    FOR(i,0,sz)
        printf("%d%c",ans2[i],(i == sz) ? '\n' : ' ');
    return 0;
}
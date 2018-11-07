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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 10000000 + 5;

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

int N,M,Q,u,v,t;
double p;
int a[MAXN];

inline bool cmp(int a,int b){
    return a > b;
}
int sum;
struct Queue{
    int num[MAXN];
    int head,tail;
    inline void clear(){
        head = 1;tail = 0;CLR(num,0);
    }

    inline const bool empty(){
        // DEBUG(head);DEBUG(tail);
        return head > tail;
    }

    inline void push(int val){
        num[++tail] = val;
    }

    inline const int front(){
        if(empty()) return -1;
        return num[head];
    }

    inline const int pop(){
        if(empty()) return -1;
        return num[head++];
    }

    inline int size(){
        return tail-head+1;
    }

}q,cut1,cut2;

signed main(){
    read(N);read(M);read(Q);read(u);read(v);read(t);
    double p=1.0*u/(1.0*v);
    FOR(i,1,N) read(a[i]);
    std::sort(a+1,a+N+1,cmp);
    q.clear();cut1.clear();cut2.clear();
    FOR(i,1,N) q.push(a[i]);
    int top,h=1;
    FOR(i,1,M){
        if(q.empty()){
            top = (cut1.front() > cut2.front()) ? cut1.pop() : cut2.pop();
        }
        else if(q.front() >= cut1.front() && q.front() >= cut2.front()) top = q.pop();
        else if(cut1.front() >= cut2.front() && cut1.front() >= q.front()) top = cut1.pop();
        else top = cut2.pop();
        // DEBUG(cut1.front());DEBUG(cut2.front());
        top += sum;
        int a1 = floor(p*(double)top),a2 = top-a1;
        sum += Q;
        a1-=sum;a2-=sum;// DEBUG(a1);DEBUG(a2);
        cut1.push(a1);cut2.push(a2);
        if(!(i%t)) printf("%lld ",top);
    }
    puts("");
    int cnt = q.size() + cut1.size() + cut2.size();DEBUG(cnt);
    FOR(i,1,cnt){
        int ans;
        if(q.front() >= cut1.front() && q.front() >= cut2.front()) ans = q.pop();
        else if(cut1.front() >= cut2.front() && cut1.front() >= q.front()) ans = cut1.pop();
        else ans = cut2.pop();
        if((i)%t==0) printf("%lld ",ans+sum);
    }puts("");
    return 0;
}

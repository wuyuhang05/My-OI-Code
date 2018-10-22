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

const int MAXN = 100000 + 5;

struct Query{
    int l,r,opt;
}q[MAXN];

int N,Q;
int a[MAXN],cnt[MAXN];
const int ha = 1000000000+7;

int main(){
    read(N);read(Q);cnt[Q] = 1;
    FOR(i,1,Q) read(q[i].opt),read(q[i].l),read(q[i].r);
    ROF(i,Q,1){
        cnt[i] = (cnt[i] + cnt[i+1]) % ha;
        if(q[i].opt & 1){
            a[q[i].l] = (a[q[i].l] + cnt[i])%ha;
            a[q[i].r+1] = (a[q[i].r+1] - cnt[i] + ha)%ha;
        }
        else{
            cnt[q[i].r] = (cnt[q[i].r] + cnt[i])%ha;
            cnt[q[i].l-1] = (cnt[q[i].l-1] - cnt[i] + ha) % ha;
        }
    }
    FOR(i,1,N){
        a[i] = (a[i] + a[i-1])%ha;
        printf("%d ",a[i]%ha);
    }
    puts("");
    return 0;
}
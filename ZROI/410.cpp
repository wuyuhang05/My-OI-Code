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

const int MAXN = 1000000 + 5;

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

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);
int cnt = 0;
struct SegmentTree{
    int l,r,sum,tag;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void cover(){
        sum = r-l+1-sum;
        tag ^= 1;
    }

    inline void pushdown(){
        if(tag){
            lc->cover();
            rc->cover();
            tag = 0;
        }
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
    }

    void modify(int L,int R){
        if(l == L && R == r){
            cover();
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R);
        else if(L > mid) rc->modify(L,R);
        else lc->modify(L,mid),rc->modify(mid+1,R);
        pushup();
    }
}pool[MAXN<<2],*frog = pool,*segt;

//#define read(x) std::cin >> x

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *res = ++frog;
    res->l = l;res->r = r;
    res->lc = lc;res->rc = rc;
    res->sum = 0;res->tag = 0;
    return res;
} 

int N,M;

int main(){
    read(N);read(M);
    segt = SegmentTree::build(1,N);
    while(M--){
        int l,r;read(l);read(r);
        segt->modify(l,r);
        //printf("%d\n",segt->sum);
    }
    printf("%d\n",segt->sum);
    return 0;
}
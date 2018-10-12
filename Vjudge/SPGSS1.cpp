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

const int MAXN = 50000 + 5;

struct Node *New(int ,int ,Node *,Node *);

struct Node{
    int l,r;LL lmax,rmax,ans,sum;
    Node *lc,*rc;

    inline void init(){
        l = r = sum = 0;
        lmax = rmax = ans = LLONG_MIN;
        lc = rc = NULL;
    }

    static Node *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        lmax = std::max(lc->lmax,lc->sum+rc->lmax);
        rmax = std::max(rc->rmax,rc->sum+lc->rmax);
        sum = lc->sum + rc->sum;
        ans = std::max(std::max(lc->ans,rc->ans),lc->rmax+rc->lmax);
    }

    inline void update(int x,int pos){
        if(l == r){
            lmax = rmax = sum = ans = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(x,pos);
        else rc->update(x,pos);
        pushup();
    }

    inline Node query(int L,int R){
        if(L == l && R == r){
            return (Node){0,0,lmax,rmax,ans,sum,NULL,NULL};
        }
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        if(L > mid) return rc->query(L,R);
        Node la = lc->query(L,mid),ra = rc->query(mid+1,R),ret;
        ret.lmax = std::max(la.lmax,la.sum+ra.lmax);
        ret.rmax = std::max(ra.rmax,ra.sum+la.rmax);
        ret.sum = la.sum + ra.sum;
        ret.ans = std::max(std::max(la.ans,ra.ans),la.rmax+ra.lmax);
        return ret;
    }

}pool[(MAXN<<1)+1],*frog = pool,*segt;

Node *New(int l,int r,Node *lc,Node *rc){
    Node *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lmax = ret->rmax = ret->ans = LLONG_MIN;
    ret->sum = 0;
    ret->lc = lc;ret->rc = rc;
    return ret;
}

int N,M;

int main(){
    read(N);
    segt = Node::build(1,N);
    FOR(i,1,N){
        int x;read(x);
        segt->update(x,i);
    }
    read(M);
    while(M--){
        int x,y;read(x);read(y);
        printf("%lld\n",segt->query(x,y).ans);
    }
    return 0;
}
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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r;
    LL lmax,rmax,mmax,sum; //前缀 max，后缀 max，跨越中点 max，和。
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
        lmax = std::max(lc->lmax,lc->sum + rc->lmax);
        rmax = std::max(rc->rmax,lc->rmax + rc->sum);
        mmax = std::max(std::max(lc->mmax,rc->mmax),lc->rmax + rc->lmax);
    }

    inline void update(int pos,int x){
        if(l == r){
            lmax = rmax = mmax = sum = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    inline SegmentTree query(int L,int R){
        if(L == l && R == r)
            return (SegmentTree){0,0,lmax,rmax,mmax,sum,NULL,NULL};
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        if(L > mid) return rc->query(L,R);
        SegmentTree lans = lc->query(L,mid),rans = rc->query(mid + 1,R),ans;
        ans.lmax = std::max(lans.lmax,lans.sum + rans.lmax);
        ans.rmax = std::max(rans.rmax,rans.sum + lans.rmax);
        ans.sum = lans.sum + rans.sum;
        ans.mmax = std::max(std::max(lans.mmax,rans.mmax),lans.rmax + rans.lmax);
        return ans;
    }
}pool[MAXN<<2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->lmax = ret->rmax = ret->mmax = INT_MIN;
    return ret;
}

int N,M;
int opt,x,y;
SegmentTree ans;

int main(){
    read(N);
    segt = SegmentTree::build(1,N);
    FOR(i,1,N){
        int x;
        read(x);
        segt->update(i,x);
    }
    read(M);
    while(M--){
        read(opt);read(x);read(y);
        if(opt){
            printf("%lld\n",segt->query(x,y).mmax);
        }
        else{
            segt->update(x,y);
        }
    }
    return 0;
}

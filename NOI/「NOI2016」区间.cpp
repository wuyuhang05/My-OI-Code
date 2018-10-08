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

const int MAXN = 500000 + 5;

struct Data{
    int l,r,ll,rr,pos; // lisan_l,lisan_r;
    int len;
    
    bool operator < (const Data &other) const {
        return len < other.len;
    }
}d[MAXN];

int N,M;
std::map<int,int> S;
#define MP std::make_pair

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,max,tag;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void cover(int delta){
        max += delta;
        tag += delta;
    }

    inline void pushdown(){
        if(tag){
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }

    inline void pushup(){
        max = std::max(lc->max,rc->max);
    }

    inline void modify(int L,int R,int delta=1){
        if(L == l && R == r){
            cover(delta);
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R,delta);
        else if(L > mid) rc->modify(L,R,delta);
        else lc->modify(L,mid,delta),rc->modify(mid+1,R,delta);
        pushup();
    }
}pool[(MAXN<<3) + 1],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->max = ret->tag = 0;
    return ret;
}

int main(){
    read(N);read(M);
    FOR(i,1,N){
        read(d[i].l);read(d[i].r);
        d[i].len = d[i].r-d[i].l + 1;d[i].pos = i;
        S.insert(MP(d[i].l,0));
        S.insert(MP(d[i].r,0));
    }
    int cnt = 0;
    for(std::map<int,int>::iterator it = S.begin();it != S.end();++it){
        it->second = ++cnt;
    }
    FOR(i,1,N){
        d[i].ll = S[d[i].l];
        d[i].rr = S[d[i].r];
    }
    std::sort(d + 1,d + N + 1);
    segt = SegmentTree::build(1,N*2);
    int last = 1,ans = INT_MAX;
    FOR(i,1,N){
        segt->modify(d[i].ll,d[i].rr);
        while(segt->max == M){
            segt->modify(d[last].ll,d[last].rr,-1);
            ans = std::min(ans,d[i].len-d[last].len);
            ++last;
        }
    }
    ans = (ans == INT_MAX) ? -1 : ans;
    printf("%d\n",ans);
    return 0;
}
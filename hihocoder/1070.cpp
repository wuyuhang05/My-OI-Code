#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 1;
    char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

const int MAXN = 1000000+5;

struct SegmentTree *New(int ,int  ,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,min;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return l == r ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        min = std::min(lc->min,rc->min);
    }

    inline void update(int pos,int x){
        if(l == r){
            min = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    int query(int L,int R){
        if(l == L && R == r) return min;
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        if(L > mid) return rc->query(L,R);
        return std::min(lc->query(L,mid),rc->query(mid+1,R));
    }
}pool[MAXN<<2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
    return ret;
}

int N,M;

int main(){
    read(N);
    segt = SegmentTree::build(1,N);
    FOR(i,1,N){
        int x;read(x);
        segt->update(i,x);
    }read(M);
    while(M--){
        int opt,x,y;read(opt);read(x);read(y);
        //DEBUG(opt);DEBUG(x);DEBUG(y);
        if(!opt){
            printf("%d\n",segt->query(x,y));
        }
        else segt->update(x,y);
    }
    system("pause");
    return 0;
}
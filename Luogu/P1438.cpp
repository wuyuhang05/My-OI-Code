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

const int MAXN = 100000+5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);
int val[MAXN];

struct SegmentTree{
    int l,r,first,delta;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return l == r ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void cover(int f,int d){
        first += f;
        delta += d;
    }

    inline void pushdown(){
        if(first || delta){
            int mid = (l + r) >> 1;
            lc->cover(first,delta);
            rc->cover(first+(mid-l+1)*delta,delta);
            first = delta = 0;
        }
    }

    inline void modify(int L,int R,int F,int D){
        if(L <= l && R >= r){
            cover((l-L)*D+F,D);
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(L <= mid) lc->modify(L,R,F,D);
        if(R > mid) rc->modify(L,R,F,D);
    }

    inline int calc(int pos){
        if(l == r){
            return val[pos] + first;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid) return lc->calc(pos);
        return rc->calc(pos);
    }
}pool[(MAXN<<2)+1],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;ret->lc = lc;ret->rc = rc;
    ret->first = ret->delta = 0;
    return ret;
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) scanf("%d",val+i);
    segt = SegmentTree::build(1,N);
    while(M--){
        int opt;scanf("%d",&opt);
        if(opt & 1){
            int L,R,K,D;
            scanf("%d%d%d%d",&L,&R,&K,&D);
            segt->modify(L,R,K,D);
        }
        else{
            int pos;scanf("%d",&pos);
            printf("%d\n",segt->calc(pos));
        }
    }
    system("pause");
    return 0;
}
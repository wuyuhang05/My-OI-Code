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

const int MAXN = 100000 + 5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

int N,M,b[MAXN];

struct SegmentTree{
    int l,r,min,sum,tag;
    // sum = ans,min 表示 Bi-Ai
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
        min = std::min(lc->min,rc->min);
    }

    inline void pushdown(){
        if(tag){
            lc->tag += tag;
            rc->tag += tag;
            lc->min -= tag;
            rc->min -= tag;
            tag = 0;
        }
    }

    inline bool cover(){
        bool ret=0;
        min--;
        if(min){
            tag++;
            ret = 1;
        }
        else{
            if(l == r){
                sum++;
                min = b[l];
                ret=1;
            }
        }
        return ret;
    }

    inline void update(int x,int pos){ // update min
        if(l == r){
            min = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(x,pos);
        else rc->update(x,pos);
        pushup();
    }
    
    inline void modify(int L,int R){ // add 1
        if(l == L && r == R){
            if(cover()) return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R);
        else if(L > mid) rc->modify(L,R);
        else{
            lc->modify(L,mid);rc->modify(mid+1,R);
        }
        pushup();
    }

    inline LL query(int L,int R){
        if(l == L && r == R)
            return sum;
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        else if(L > mid) return rc->query(L,R);
        else return lc->query(L,mid) + rc->query(mid+1,R);
    }
}pool[MAXN << 2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->min = ret->sum = ret->tag = 0;
    return ret;
}

inline void solve(){
    frog = pool;
    FOR(i,1,N) std::cin >> b[i];
    segt = SegmentTree::build(1,N);
    FOR(i,1,N) segt->update(b[i],i);
    char opt[sizeof("query") + 5];
    int l,r;
    while(M--){
        std::cin >> opt >> l >> r;
        if(opt[0] == 'a'){
            segt->modify(l,r);
        }
        else{
            printf("%lld\n",segt->query(l,r));
        }
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    while(std::cin >> N >> M) solve();
    return 0;
}
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

const int MAXN = 400000 + 5;
char str[MAXN];
int N,Q;

struct SegmentTree *ans;

SegmentTree *New(int,int,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,la,ra,a;
    SegmentTree *lc,*rc;

    static SegmentTree *setup(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,setup(l,mid),setup(mid + 1,r));
    }

    inline void pushup(){
        int t = std::min(lc->la,rc->ra);
        a = lc->a + rc->a + t;
        la = lc->la + rc->la - t;
        ra = lc->ra + rc->ra - t;
    }

    inline void build(){
        if(l == r){
            str[l] == '(' ? la++ : ra++;
            return;
        }
        lc->build();rc->build();
        pushup();
    }

    inline void query(int left,int right){
        if(left == l && right == r){
            int t = std::min(ra,ans->la);
            ans->a += t + a;
            ans->la += la - t;
            ans->ra += ra - t;
            return;
        }
        int mid = (l + r) >> 1;
        if(right <= mid) lc->query(left,right);
        else if(left > mid) rc->query(left,right);
        else lc->query(left,mid),rc->query(mid + 1,right);
    }
}pool[MAXN << 2],*frog = pool,*segt;

SegmentTree *New(int l=1,int r=N,SegmentTree *lc=NULL,SegmentTree *rc=NULL){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->la = ret->ra = ret->a = 0;
    return ret;
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin >> N >> Q;
    std::cin >> (str+1);
    segt = SegmentTree::setup(1,N);
    segt->build();
    ans = New();
    while(Q--){
        int l,r;
        std::cin >> l >> r;
        ans->la = ans->ra = ans->a = 0;
        segt->query(l,r);
        printf("%d\n",ans->a << 1);
    }
    return 0;
}


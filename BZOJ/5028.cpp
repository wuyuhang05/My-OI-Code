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
#define int LL
const int MAXN = 100000+5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

int _gcd(int a,int b){
    return (!b) ? a : _gcd(b,a%b);
}

struct SegmentTree{
    int l,r,gcd,sum;
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    void pushup(){
        gcd = _gcd(lc->gcd,rc->gcd);
        sum = lc->sum + rc->sum;
    }

    void update(int pos,int x){
        if(l == r){
            gcd += x;sum += x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    int querygcd(int L,int R){
        if(L > R) return 0;
        if(L == l && R == r) return gcd;
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->querygcd(L,R);
        if(L > mid) return rc->querygcd(L,R);
        return _gcd(lc->querygcd(L,mid),rc->querygcd(mid+1,R));
    }

    int querysum(int L,int R){
        //if(L > R) return 0;
        if(L == l && R == r) return sum;
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->querysum(L,R);
        if(L > mid) return rc->querysum(L,R);
        return lc->querysum(L,mid)+rc->querysum(mid+1,R);
    }
}pool[MAXN<<2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->gcd = 0;ret->sum = 0;
    return ret;
}

int N,M;
int a[MAXN],c[MAXN];

signed main(){
    scanf("%lld%lld",&N,&M);
    segt = SegmentTree::build(1,N);
    FOR(i,1,N){
        scanf("%lld",a+i);
        segt->update(i,a[i]-a[i-1]);
    }
    while(M--){
        int opt,l,r;scanf("%lld%lld%lld",&opt,&l,&r);
        if(opt == 1) printf("%ld\n",std::labs(_gcd(segt->querysum(1,l),segt->querygcd(l+1,r))));
        else{
            int x;scanf("%lld",&x);
            segt->update(l,x);
            if(r < N) segt->update(r+1,-x);
        }
    }
    return 0;
}
/*
3 4
2 3 4
1 1 3
2 2 2 1
1 1 3
1 2 3	
*/
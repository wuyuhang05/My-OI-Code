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

const int MAXN = 200000 + 5;

struct Node *New(int ,int ,Node *,Node *);

struct Node{
    int l,r;
    LL sum,max;
    Node *lc,*rc;

    static Node *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    inline void pushup(){
        sum = lc->sum + rc->sum;
        max = std::max(lc->max,rc->max);
    }

    inline void update(LL x,int pos){
        if(l == r){
            max = sum = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(x,pos);
        else rc->update(x,pos);
        pushup();
    }

    inline void modify(int L,int R){
        if(max <= 1) return;
        if(l == r && L <= l && R >= r){
            max = sum = std::sqrt(sum);
            return;
        }
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R);
        else if(L > mid) rc->modify(L,R);
        else lc->modify(L,mid),rc->modify(mid+1,R);
        pushup();
    }

    inline LL query(int L,int R){
        if(l == L && r == R) return sum;
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        if(L > mid) return rc->query(L,R);
        return lc->query(L,mid)+rc->query(mid+1,R);
    }
}pool[MAXN<<2],*frog = pool,*segt;

Node *New(int l,int r,Node *lc,Node *rc){
    Node *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = 0ll;ret->max = LLONG_MIN;
    return ret;
}

int N,M,ts;

inline void Solve(){
    // printf("Case #%d:\n",++ts);
    segt = Node::build(1,N);
    FOR(i,1,N){
        LL x;scanf("%lld",&x);
        segt->update(x,i);
    }
    scanf("%d",&M);
    while(M--){
        int opt,x,y;
        scanf("%d%d%d",&opt,&x,&y);
        if(x > y) std::swap(x,y);
        if(opt){
            printf("%lld\n",segt->query(x,y));
        }
        else{
            segt->modify(x,y);
        }
    }
    puts("");
}

int main(){
    while(~scanf("%d",&N)) Solve();
    return 0;
}
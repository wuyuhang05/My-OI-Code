#include <iostream>
#include <cstring>
#include <cstdio>
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,sum,tag;
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }
    
    inline void pushup(){
        sum = lc->sum + rc->sum; 
    }
    
    inline void cover(int delta){
        sum = (r-l+1)*delta;
        tag = delta;
    }
    
    inline void pushdown(){
        if(tag != -1){
            lc->cover(tag);
            rc->cover(tag);
            tag = -1;
        }
    }
    
    void modify(int L,int R,int x){
        if(L == l && R == r){
            cover(x);
            return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R,x);
        else if(L > mid) rc->modify(L,R,x);
        else lc->modify(L,mid,x),rc->modify(mid+1,R,x);
        pushup();
    }
    
    int query(int L,int R){
        if(L == l && R == r) return sum;
        pushdown();
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        else if(L > mid) return rc->query(L,R);
        return lc->query(L,mid) + rc->query(mid+1,R);
    }
}pool[MAXN<<2],*frog = pool,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = 0;ret->tag = -1;
    return ret;
}

int N,M;
int a[MAXN],pos;

struct Data{
    int l,r,opt;
}d[MAXN];

inline bool check(int k){ // Answer_pos >= k_pos ? 
    FOR(i,1,N) segt->modify(i,i,(a[i] >= k) ? 1 : 0);
    FOR(i,1,M){
        int l = d[i].l,r = d[i].r,opt = d[i].opt;
        int t = segt->query(d[i].l,d[i].r); // 1
        // printf("%d %d %d %d\n",l,r,opt,t);
        //DEBUG(l);DEBUG(r);DEBUG(t);
        if(opt){
            if(l <= l+t-1) segt->modify(l,l+t-1,1);
            if(l+t <= r) segt->modify(l+t,r,0);
            
            // [l,l+t-1]:1 [l+t,r]:0
        }
        else{ // 31 37 1 7
            if(l <= r-t) segt->modify(l,r-t,0);
            if(r-t+1 <= r) segt->modify(r-t+1,r,1);
            // [l,r-t]:0 [r-t+1,r]:1
        }
    }
    int ans = segt->query(pos,pos);
    return ans == 1;
}

int main(){
    scanf("%d%d",&N,&M);
    segt = SegmentTree::build(1,N);
    FOR(i,1,N) scanf("%d",a+i);
    FOR(i,1,M) scanf("%d%d%d",&d[i].opt,&d[i].l,&d[i].r);
    scanf("%d",&pos);
    int l = 1,r = N,ans;
    while(l <= r){
        DEBUG(l);DEBUG(r);
        int mid = (l + r) >> 1;
        if(check(mid)) l = mid+1,ans = mid;
        else r = mid - 1;
    }
    printf("%d\n",ans);
    return 0;
}

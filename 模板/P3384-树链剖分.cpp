#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

const int MAXN = 1000000 + 5;

#define LL long long
#define ULL unsigned long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int N,M,R,ha;
LL dist[MAXN];

struct Node{
    int dfn,size,depth;
    bool vis;
    Node *fa,*maxchild;
    struct Edge *firstEdge;
    struct Chain *chain;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool1[MAXN << 1],*frog1 = pool1;

Edge *New1(Node *s,Node *t){
    Edge *ret = ++frog1;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New1(&node[u],&node[v]);
    node[v].firstEdge = New1(&node[v],&node[u]);
}

struct Chain{
    Node *top;
}pool2[MAXN],*frog2 = pool2;

Chain *New2(Node *top){
    Chain *ret = ++frog2;
    ret->top = top;
    return ret;
}

void dfs1(Node *v){
    v->size = 1;
    v->vis = true;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->vis){
            e->t->fa = v;
            e->t->depth = v->depth + 1;
            dfs1(e->t);
            v->size += e->t->size;
            if(!v->maxchild || v->maxchild->size < e->t->size)
                v->maxchild = e->t;
        }
    }
}

void dfs2(Node *v){
    static int ts = 0;
    
    v->dfn = ++ts;
    if(!v->fa || v->fa->maxchild != v)
        v->chain = New2(v);
    else v->chain = v->fa->chain;
    if(v->maxchild)
        dfs2(v->maxchild);
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->fa == v && e->t != v->maxchild)
            dfs2(e->t);
    }
}

inline void split(int root){
    node[root].depth = 1;
    dfs1(&node[root]);
    dfs2(&node[root]);
}

struct SegmentTree;
SegmentTree *New3(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree {
    int l,r;
    LL sum,tag;
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New3(l,r,NULL,NULL) : New3(l,r,build(l,mid),build(mid + 1,r));
    }
    
    inline void pushup(){
        sum = (lc->sum + rc->sum) % ha;
    }
    
    inline void cover(LL delta){
        sum = (sum + ((r - l + 1) * delta) % ha) % ha;
        tag = (tag + delta) % ha;
    }
    
    inline void pushdown(){
        if(tag){
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }
    
    void update(int pos,LL x){
        if(l == r){
            sum = x;
            return;
        }
        LL mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }
    
    void modify(int left,int right,LL delta){
        if(left == l && right == r){
            cover(delta);
            return;
        }
        if(left > r || right < l) return;
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) lc->modify(left,right,delta);
        else if(left > mid) rc->modify(left,right,delta);
        else{
            lc->modify(left,mid,delta);
            rc->modify(mid + 1,right,delta);
        }
        pushup();
    }
    
    LL query(int left,int right){
        if(left == l && right == r) return sum%ha;
        if(left > r || right < l) return 0;
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) return lc->query(left,right);
        else if(left > mid) return rc->query(left,right);
        return (lc->query(left,mid) + rc->query(mid + 1,right))%ha;
    }
}pool3[MAXN << 2],*frog3 = pool3,*segt;

SegmentTree *New3(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog3;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = ret->tag = 0;
    return ret;
}

inline void update(int x,LL delta){
    Node *v = &node[x];
    segt->update(v->dfn,delta);
}

inline void modify1(int x,int y,LL delta){
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        segt->modify(u->chain->top->dfn,u->dfn,delta);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    segt->modify(u->dfn,v->dfn,delta);
}

inline LL query1(int x,int y){
    Node *u = &node[x],*v = &node[y];
    LL ret = 0;
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        ret = (ret + segt->query(u->chain->top->dfn,u->dfn)) % ha;
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    ret = (ret + segt->query(u->dfn,v->dfn)) % ha;
    return ret;
}

inline void modify2(int x,LL delta){
    Node *v = &node[x];
    segt->modify(v->dfn,v->dfn + v->size - 1,delta);
}

inline LL query2(int x){
    Node *v = &node[x];
    return segt->query(v->dfn,v->dfn + v->size - 1) % ha;
}

int main(){
    scanf("%d%d%d%d",&N,&M,&R,&ha);
    segt = SegmentTree::build(1,N);
    for(int i = 1;i <= N;i++)
        scanf("%lld",dist + i);
    for(int u,v,i = 1;i < N;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    split(R);
    for(int i = 1;i <= N;i++)
        update(i,dist[i]);
    int opt,x,y;LL delta;
    while(M--){
        scanf("%d",&opt);
        switch(opt){
            case 1:
                scanf("%d%d%lld",&x,&y,&delta);
                modify1(x,y,delta);
                break;
            case 2:
                scanf("%d%d",&x,&y);
                printf("%lld\n",query1(x,y)%ha);
                break;
            case 3:
                scanf("%d%lld",&x,&delta);
                modify2(x,delta);
                break;
            case 4:
                scanf("%d",&x);
                printf("%lld\n",query2(x)%ha);
                break;
        }
    }
    return 0;
}

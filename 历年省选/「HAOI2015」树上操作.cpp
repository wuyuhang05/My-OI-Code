#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

LL N,M;

struct Data{
    LL u,v,w;
}d[MAXN];

inline void Read(LL &x){
    char ch = getchar();
    x = 0;int flag = 1;
    for(;!isdigit(ch);ch = getchar())
        if(ch == '-') flag = -1;
    for(;isdigit(ch);ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    x *= flag;
}

struct Node{
    LL dfn,size,depth;
    bool vis;
    struct Edge *firstEdge;
    struct Chain *chain;
    Node *fa,*maxChild;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool1[MAXN * 2],*frog1 = pool1;

Edge *New(Node *u,Node *v){
    Edge *ret = ++frog1;
    ret->s = u;ret->t = v;
    ret->next = u->firstEdge;
    return ret;
}

inline void add(LL u,LL v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
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
    v->vis = true;
    v->size = 1;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->vis){
            e->t->fa = v;
            e->t->depth = v->depth + 1;
            dfs1(e->t);
            v->size += e->t->size;
            if(!v->maxChild || e->t->size > v->maxChild->size)
                v->maxChild = e->t;
        }
    }
}

void dfs2(Node *v){
    static LL ts = 0;
    v->dfn = ++ts;
    
    if(!v->fa || v->fa->maxChild != v)
        v->chain = New2(v);
    else v->chain = v->fa->chain;
    if(v->maxChild) dfs2(v->maxChild);
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->fa == v && e->t != v->maxChild)
            dfs2(e->t);
    }
}

inline void split(){
    node[1].depth = 1;
    dfs1(&node[1]);
    dfs2(&node[1]);
}

struct SegmentTree;
SegmentTree *New3(LL,LL,SegmentTree *,SegmentTree *);

struct SegmentTree{
    LL l,r;
    LL sum,tag;
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(LL l,LL r){
        LL mid = (l + r) / 2;
        return (l == r) ? New3(l,r,NULL,NULL) : New3(l,r,build(l,mid),build(mid + 1,r));
    }
    
    void pushup(){
        sum = lc->sum + rc->sum;
    }
    
    void cover(LL delta){
        sum += (r - l + 1) * delta;
        tag += delta;
    }
    
    void pushdown(){
        if(tag){
            lc->cover(tag);
            rc->cover(tag);
            tag = 0;
        }
    }
    
    void update(LL pos,LL x){
        if(l == r){
            sum = x;
            tag = 0;
            return;
        }
        pushdown();
        LL mid = (l + r) / 2;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }
    
    void modify(LL left,LL right,LL delta){
        if(left == l && right == r){
            cover(delta);
            return;
        }
        pushdown();
        LL mid = (l + r) >> 1;
        if(right <= mid) lc->modify(left,right,delta);
        else if(left > mid) rc->modify(left,right,delta);
        else{
            lc->modify(left,mid,delta);
            rc->modify(mid + 1,right,delta);
        }
        pushup();
    }
    
    LL query(LL left,LL right){
        if(left > r || right < l) return 0;
        if(left == l && right == r) return sum;
        pushdown();
        LL mid = (l + r) >> 1;
        if(right <= mid) return lc->query(left,right);
        else if(left > mid) return rc->query(left,right);
        else{
            return lc->query(left,mid) + rc->query(mid + 1,right);
        }
    }
}pool3[MAXN * 4],*frog3 = pool3,*segt;

SegmentTree *New3(LL l,LL r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog3;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = ret->tag = 0;
    return ret;
}

inline void modify(LL x,LL y,LL delta){
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        segt->modify(u->chain->top->dfn,u->dfn,delta);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    segt->modify(u->dfn,v->dfn,delta);
}

inline LL query(LL x,LL y){
    LL ret = 0;
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        ret += segt->query(u->chain->top->dfn,u->dfn);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    return ret + segt->query(u->dfn,v->dfn);
}

int main(){
    LL w[MAXN];
    Read(N);Read(M);
    segt = SegmentTree::build(1,N);
    for(LL i = 1;i <= N;i++){
        Read(w[i]);
    }
    for(LL u,v,i = 1;i < N;i++){
        Read(u);Read(v);
        add(u,v);
    }
    split();
    for(LL i = 1;i <= N;i++)
        segt->update(node[i].dfn,w[i]);
    for(LL opt,x,a,i = 1;i <= M;i++){
        Read(opt);Read(x);
        if(opt == 1){
            Read(a);
            modify(x,x,a);
        }
        if(opt == 2){
            Read(a);
            segt->modify(node[x].dfn,node[x].dfn + node[x].size - 1,a);
        }
        if(opt == 3)
            printf("%lld\n",query(1,x));
        
    }
    return 0;
}

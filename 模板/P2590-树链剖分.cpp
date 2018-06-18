#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>

const int MAXN = 30000 + 5;

inline void Read(int &x){ //随手读优
    char ch = getchar();
    x = 0;
    int flag = 1;
    for(;!isdigit(ch);ch = getchar())
        if(ch == '-') flag = -1;
    for(;isdigit(ch);ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    x *= flag;
}

struct SegmentTree;

struct Node{
    struct Edge *firstEdge;
    struct Chain *chain;//记录该结点所在的链
    Node *fa,*maxChild;
    //记录父结点和子结点最多的子结点
    int size,dfn,pos,depth;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}edge_pool[MAXN * 2],*edge_frog = edge_pool;

Edge *New_Edge(Node *s,Node *t){
    Edge *ret = ++edge_frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

struct Chain{
    Node *top;
    int len;
}chain_pool[MAXN],*chain_frog = chain_pool;

Chain *New_Chain(Node *top){
    Chain *ret = ++chain_frog;
    ret->top = top;ret->len = 0;
    return ret;
}

inline void add_edge(int u,int v){
    node[u].firstEdge = New_Edge(&node[u],&node[v]);
    node[v].firstEdge = New_Edge(&node[v],&node[u]);
}

SegmentTree *New_SegmentTree(int,int,SegmentTree*,SegmentTree*);

struct SegmentTree{
    int l,r,sum,max,sum_tag,max_tag,mid;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        if(l == r) return New_SegmentTree(l,r,NULL,NULL);
        int mid = l + (r - l) / 2;
        return New_SegmentTree(l,r,build(l,mid),build(mid + 1,r));
    }

    void pushDown(){
        if(sum_tag){
            lc->sum += sum_tag;
            rc->sum += sum_tag;
            sum_tag = 0;
        }
        if(max_tag){
            lc->max = std::max(lc->max,max_tag);
            rc->max = std::max(rc->max,max_tag);
            max_tag = 0;
        }
    }

    void cover(int delta){
        sum += (this->r - this->l + 1) * delta;
        sum_tag += delta;
    }

    void maintain(){
        sum = lc->sum + rc->sum;
        max = std::max(lc->max,rc->max);
    }

   void modify(int l,int r,int delta){
        if(l > this->r || r < this->l) return;
        if(l <= this->l && r >= this->r) cover(delta);
        else{
            pushDown();
            lc->modify(l,r,delta);
            rc->modify(l,r,delta);
            maintain();
        }
    }

    void update(int pos,int delta){
        if(l == r) sum = max = delta;
        else{
            int mid = l + (r - l) / 2;
            if(pos <= mid) lc->update(pos,delta);
            else rc->update(pos,delta);
            maintain();
        }
    }

    int query_sum(int l,int r){
        if(l > this->r || r < this->l) return 0;
        if(l <= this->l && r >= this->r) return sum;
        return pushDown(),lc->query_sum(l,r) + rc->query_sum(l,r);
    }

    int query_max(int l,int r){
        if(l > this->r || r < this->l) return INT_MIN;
        if(l <= this->l && r >= this->r) return max;
        return pushDown(),std::max(lc->query_max(l,r),rc->query_max(l,r));
    }

}SegmentTree_pool[MAXN * 4],*SegmentTree_frog = SegmentTree_pool,*segt;

SegmentTree *New_SegmentTree(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++SegmentTree_frog;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->max = INT_MIN;
    ret->sum = ret->max_tag = ret->sum_tag = 0;
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
            if(!v->maxChild || v->maxChild->size < e->t->size) v->maxChild = e->t;
        }
    }
}

void dfs2(Node *v){
    static int timer = 0;
    v->dfn = ++timer;

    if(!v->fa || v != v->fa->maxChild)
        v->chain = New_Chain(v);
    else {
        v->chain = v->fa->chain;
        v->pos = ++v->chain->len;
    }

    if(v->maxChild) dfs2(v->maxChild);

    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->fa == v && e->t != v->maxChild){
            dfs2(e->t);
        }
    }
}

inline void split(){
    node[1].depth = 1;
    dfs1(&node[1]);
    dfs2(&node[1]);
}

inline void modify(int v,int x){
    segt->update(node[v].dfn,x);
}

int query_sum(int a,int b){
    Node *u = &node[a],*v = &node[b];
    int ret = 0;
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        ret += segt->query_sum(u->chain->top->dfn,u->dfn);
        u = u->chain->top->fa;
    }

    if(u->depth > v->depth) std::swap(u,v);
    ret += segt->query_sum(u->dfn,v->dfn);

    return ret;
}

int query_max(int a,int b){
    Node *u = &node[a],*v = &node[b];
    int ret = INT_MIN;
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        ret = std::max(ret,segt->query_max(u->chain->top->dfn,u->dfn));
        u = u->chain->top->fa;
    }

    if(u->depth > v->depth) std::swap(u,v);
    ret = std::max(ret,segt->query_max(u->dfn,v->dfn));

    return ret;
}

inline Node *lca(Node *u,Node *v){
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        u = u->chain->top->fa;
    }

    if(u->depth > v->depth) std::swap(u,v);
    return u;
}

int main(){
    int N;Read(N);
    for(int u,v,i = 1;i < N;i++){
        Read(u);Read(v);
        add_edge(u,v);
    }
    split();
    segt = SegmentTree::build(1,N);
    for(int x,i = 1;i <= N;i++){
        Read(x);
        modify(i,x);
    }
    int q;Read(q);
    while(q--){
        char cmd[sizeof("CHANGE")];
        int a,b;
        scanf("%s",cmd);
        Read(a);Read(b);
        if(cmd[1] == 'H')
            modify(a,b);
        if(cmd[1] == 'M')
            printf("%d\n",query_max(a,b));
        if(cmd[1] == 'S')
            printf("%d\n",query_sum(a,b));
    }
    return 0;
}

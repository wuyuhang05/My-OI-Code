#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>

const int MAXN = 100000 + 5;

int N;

struct Data{
    int u,v,w;
}e[MAXN];

struct Node{
    struct Edge *firstEdge;
    struct Chain *chain;
    Node *fa,*maxChild;
    int size,dfn,depth;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool1[MAXN * 2],*frog1 = pool1;

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
    v->size = 1;v->vis = true;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->vis) continue;
        e->t->fa = v;
        e->t->depth = v->depth + 1;
        dfs1(e->t);
        v->size += e->t->size;
        if(!v->maxChild || v->maxChild->size < e->t->size)
            v->maxChild = e->t;
    }
}

void dfs2(Node *v){
    static int ts = 0;
    v->dfn = ++ts;
    if(!v->fa || v->fa->maxChild != v) v->chain = New2(v);
    else v->chain = v->fa->chain;
    if(v->maxChild)
        dfs2(v->maxChild);
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(v->maxChild != e->t && e->t->fa == v)
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

struct SegmentTree{
    int l,r,max,tag1,tag2; // tag1 = delta,tag2 = modify
    SegmentTree *lc,*rc;
    
    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New3(l,r,NULL,NULL) : New3(l,r,build(l,mid),build(mid + 1,r));
    }
    
    inline void pushup(){
        max = std::max(lc->max,rc->max);
    }
    
    inline void cover1(int delta){ // delta
        max += delta;
        tag1 += delta;
    }
    
    inline void cover2(int delta){ // modify
        max = delta;
        tag2 = delta;
        tag1 = 0;
    }
    
    inline void pushdown(){ // ???
        if(tag2 != -1){
            lc->cover2(tag2);
            rc->cover2(tag2);
            lc->tag1 = rc->tag1 = 0;
            tag2 = -1;
        }
        if(tag1){
            lc->cover1(tag1);
            rc->cover1(tag1);
            tag1 = 0;
        }
    }
    
    inline void update(int pos,int x){
        if(l == r){
            max = x;tag1 = tag2 = 0;return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }
    
    void modify1(int left,int right,int delta){ // delta
        if(l == left && r == right){
            cover1(delta);return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) lc->modify1(left, right, delta);
        else if(left > mid) rc->modify1(left, right, delta);
        else{
            lc->modify1(left, mid, delta);
            rc->modify1(mid + 1, right, delta);
        }
        pushup();
    }
    
    void modify2(int left,int right,int delta){ // modi
        if(l == left && r == right){
            cover2(delta);return;
        }
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) lc->modify2(left, right, delta);
        else if(left > mid) rc->modify2(left, right, delta);
        else{
            lc->modify2(left,mid,delta);
            rc->modify2(mid + 1,right,delta);
        }
        pushup();
    }
    
    int query(int left,int right){
        if(l == left && r == right) return max;
        // if(right < l || left > r) return INT_MIN;
        pushdown();
        int mid = (l + r) >> 1;
        if(right <= mid) return lc->query(left,right);
        if(left > mid) return rc->query(left, right);
        return std::max(lc->query(left,mid),rc->query(mid + 1,right));
    }
}pool3[MAXN*4],*frog3 = pool3,*segt;

SegmentTree *New3(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog3;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->max = INT_MIN;
    ret->tag1 = 0;ret->tag2 = -1;
    return ret;
}

Node *lca(int x,int y){
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    return u;
}

inline void Change(int pos,int x){
    // segt->update(node[e[pos].u].dfn,x);
    int u = node[e[pos].u].depth > node[e[pos].v].depth ? e[pos].u : e[pos].v;
    segt->update(node[u].dfn,x);
}

inline void Cover_Point(int x,int y,int delta){
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        segt->modify2(u->chain->top->dfn,u->dfn,delta);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    segt->modify2(u->dfn,v->dfn,delta);
}

inline void Cover(int x,int y,int delta){
    Node *l = lca(x,y);
    int last = segt->query(l->dfn,l->dfn);
    Cover_Point(x,y,delta);
    segt->update(l->dfn,last);
}

inline void Add_Point(int x,int y,int delta){
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        segt->modify1(u->chain->top->dfn,u->dfn,delta);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    segt->modify1(u->dfn,v->dfn,delta);
}

inline void Add(int x,int y,int delta){
    Node *l = lca(x,y);
    int last = segt->query(l->dfn,l->dfn);
    Add_Point(x,y,delta);
    segt->update(l->dfn,last);
}

inline int Max_Point(int x,int y){
    Node *u = &node[x],*v = &node[y];
    int ret = INT_MIN;
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        ret = std::max(ret,segt->query(u->chain->top->dfn,u->dfn));
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    return std::max(ret,segt->query(u->dfn,v->dfn));
}

inline int Max(int x,int y){
    Node *l = lca(x,y);
    int last = segt->query(l->dfn,l->dfn);
    segt->update(l->dfn,INT_MIN);
    int ret = Max_Point(x,y);
    segt->update(l->dfn,last);
    return ret;
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i < N;i++){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
        add(e[i].u,e[i].v);
    }
    split(1);
    segt = SegmentTree::build(1,N);
    for(int i = 1;i < N;i++){
        if(node[e[i].u].depth < node[e[i].v].depth) std::swap(e[i].u,e[i].v);
        segt->update(node[e[i].u].dfn,e[i].w);
    }
    char str[sizeof("Change") + 1];
    int x,y,z;
    while(str[0] != 'S'){
        scanf("%s",str);
        if(str[1] == 'h'){
            scanf("%d%d",&x,&y);
            Change(x,y);
        }
        if(str[1] == 'o'){
            scanf("%d%d%d",&x,&y,&z);
            Cover(x,y,z);
        }
        if(str[1] == 'd'){
            scanf("%d%d%d",&x,&y,&z);
            Add(x,y,z);
        }
        if(str[1] == 'a'){
            scanf("%d%d",&x,&y);
            printf("%d\n",Max(x,y));
        }
    }
    return 0;
}


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

const int MAXN = 100000 + 5;

namespace fastIO{ 
    #define BUF_SIZE 100000 
    #define OUT_SIZE 100000 
    #define ll long long 
    bool IOerror=0; 
    inline char nc(){ 
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE; 
        if (p1==pend){ 
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin); 
            if (pend==p1){IOerror=1;return -1;} 
        } 
        return *p1++; 
    } 
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';} 
    inline void read(int &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    inline void read(ll &x){ 
        bool sign=0; char ch=nc(); x=0; 
        for (;blank(ch);ch=nc()); 
        if (IOerror)return; 
        if (ch=='-')sign=1,ch=nc(); 
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0'; 
        if (sign)x=-x; 
    } 
    #undef ll 
    #undef OUT_SIZE 
    #undef BUF_SIZE 
}; 
using namespace fastIO;
#define int long long

struct Node{
    struct Edge *firstEdge;
    int dfn,depth,size;
    // bool vis;
    Node *fa,*maxChild;
    struct Chain *chain;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN<<1],*frog = pool;

struct Chain{
    Node *top;
}pool2[MAXN],*frog2 = pool2;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

Chain *New(Node *top){
    Chain *ret = ++frog2;
    ret->top = top;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

void dfs1(Node *v){
    v->size = 1;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->size){
            e->t->fa = v;
            e->t->depth = v->depth + 1;
            dfs1(e->t);
            v->size += e->t->size;
            if(!v->maxChild || v->maxChild->size < e->t->size)
                v->maxChild = e->t;
        }
    }
}

void dfs2(Node *v){
    static int ts = 0;
    v->dfn = ++ts;
    if(!v->fa || v->fa->maxChild != v) v->chain = New(v);
    else v->chain = v->fa->chain;
    if(v->maxChild) dfs2(v->maxChild);
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->fa == v && e->t != v->maxChild) dfs2(e->t);
    }
}

inline void split(int root){
    node[root].depth = 1;
    dfs1(&node[root]);
    dfs2(&node[root]);
}

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
    int l,r,sum,max,tag;
    SegmentTree *lc,*rc;

    static SegmentTree *build(int l,int r){
        int mid = (l + r) >> 1;
        return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid+1,r));
    }

    void pushup(){
        max = std::max(lc->max,rc->max);
        sum = lc->sum + rc->sum;
    }

    void update(int pos,int x){
        if(l == r){
            max = sum = x;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) lc->update(pos,x);
        else rc->update(pos,x);
        pushup();
    }

    void modify(int L,int R,int p){
        if(max < p) return;
        // if(L == l && R == r){
        //     sum %= p;return;
        // }
        if(l == r && L <= l && l >= R){
            sum %= p;max %= p;
            return;
        }
        // if(L > r || R < l) return;
        int mid = (l + r) >> 1;
        if(R <= mid) lc->modify(L,R,p);
        else if(L > mid) rc->modify(L,R,p);
        else lc->modify(L,mid,p),rc->modify(mid+1,R,p);
        pushup();
    }

    LL query(int L,int R){
        if(L == l && R == r) return sum;
        int mid = (l + r) >> 1;
        if(R <= mid) return lc->query(L,R);
        if(L > mid) return rc->query(L,R);
        return lc->query(L,mid)+rc->query(mid+1,R);        
    }
}pool1[MAXN<<2],*frog1 = pool1,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
    SegmentTree *ret = ++frog1;
    ret->l = l;ret->r = r;
    ret->lc = lc;ret->rc = rc;
    ret->sum = ret->max = 0;
    return ret;
}

LL queryline(int x,int y){
    LL res = 0ll;
    Node *u = &node[x],*v = &node[y];
    while(u->chain != v->chain){
        if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
        res += segt->query(u->chain->top->dfn,u->dfn);
        u = u->chain->top->fa;
    }
    if(u->depth > v->depth) std::swap(u,v);
    return res + segt->query(u->dfn,v->dfn);
}

int N,M;

signed main(){
    freopen("flower.in","r",stdin);
    freopen("flower.out","w",stdout);
    read(N);read(M);
    FOR(i,1,N-1){
        int u,v;read(u);read(v);
        add(u,v);
    }
    // DEBUG(N);
    segt = SegmentTree::build(1,N);
    split(1);
    FOR(i,1,N){
        int x;read(x);
        segt->update(node[i].dfn,x);
    }
    while(M--){
        int opt,x,y;
        read(opt);read(x);read(y);
        if(opt == 1){
            //DEBUG(node[x].dfn);DEBUG(node[x].dfn+node[x].size-1);
            segt->modify(node[x].dfn,node[x].dfn+node[x].size-1,y);
        }
        if(opt == 2){
            segt->update(node[x].dfn,y);
        }
        if(opt == 3){
            printf("%lld\n",queryline(x,y));
        }
    }
    return 0;
}
/*
8 7
1 2
2 3
2 4
2 5
1 6
6 7
6 8
1 2 3 4 5 6 7 8
3 3 6
1 2 3
2 2 4
3 4 8
2 3 11
1 1 5
3 3 7
*/
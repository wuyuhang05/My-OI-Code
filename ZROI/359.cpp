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

const int MAXN = 100000 + 5;

struct Node{
    struct GEdge *firstEdge;
    int dist,pos;
    bool used,vis;
}node[MAXN];

struct Tree{
    struct TEdge *firstEdge;
    int dfn,low;bool vis;
}tree[MAXN];

struct GEdge{
    Node *s,*t;
    int w,pos;
    GEdge *next;
}pool1[MAXN*2],*frog1=pool1;

struct TEdge{
    Tree *s,*t;
    int pos;
    TEdge *next;
}pool2[MAXN*2],*frog2=pool2;

GEdge *New(Node *s,Node *t,int w,int pos){
    GEdge *ret = ++frog1;
    ret->s = s;ret->t = t;ret->pos = pos;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

TEdge *New(Tree *s,Tree *t,int pos){
    TEdge *ret = ++frog2;
    ret->s = s;ret->t = t;
    ret->pos = pos;
    ret->next = s->firstEdge;
    return ret;
}

inline void Gadd(int u,int v,int w,int pos){
    node[u].firstEdge = New(&node[u],&node[v],w,pos);
    node[v].firstEdge = New(&node[v],&node[u],w,pos);
}

inline void Tadd(int u,int v,int pos){
    tree[u].firstEdge = New(&tree[u],&tree[v],pos);
    tree[v].firstEdge = New(&tree[v],&tree[u],pos);
}

int N,M;

inline void dijkstra(){
    #define EFOR(i,v) for(GEdge *i = v->firstEdge;i;i = i->next)
    #define P std::pair<int,Node *>
    #define MP std::make_pair
    FOR(i,1,N){
        node[i].dist = INT_MAX;
        node[i].used = false;
        node[i].pos = i;
    }
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(0,&node[1]));
    node[1].dist = 0ll;
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        if(v->used) continue;
        v->used = true;
        EFOR(e,v){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                q.push(MP(e->t->dist,e->t));
            }
        }
    }
    #undef P
    #undef MP
    #undef EFOR
}

inline void build(Node *v){
    #define EFOR(i,v) for(GEdge *i = v->firstEdge;i;i = i->next)
    v->vis = true;
    EFOR(e,v){
        if(v->dist == e->t->dist + e->w){
            // printf("%d %d\n",v->pos,e->t->pos);
            Tadd(v->pos,e->t->pos,e->pos);
            if(!e->t->vis) build(e->t);
        }
    }
    #undef EFOR
}

std::priority_queue<int,std::vector<int>,std::greater<int> > ans;

void dfs(Tree *v,TEdge *Fe){
    #define EFOR(i,v) for(TEdge *i = v->firstEdge;i;i = i->next)
    static int ts = 0;
    // DEBUG(ts);
    v->dfn = v->low = ++ts;
    v->vis = true;
    EFOR(e,v){
        if(!e->t->vis){
            dfs(e->t,e);
            v->low = std::min(v->low,e->t->low);
            // DEBUG(e->t->low);DEBUG(v->dfn);
            if(e->t->low > v->dfn) ans.push(e->pos);
        }
        else if(e->pos != Fe->pos) v->low = std::min(v->low,e->t->dfn);
    }
    #undef EFOR
}

int main(){
    read(N);read(M);
    FOR(i,1,M){
        int u,v,w;read(u);read(v);read(w);
        Gadd(u,v,w,i);
    }
    dijkstra();
    build(&node[N]);
    TEdge *nil = (TEdge *) malloc (sizeof(TEdge));
    nil->pos = -1;
    dfs(&tree[1],nil);
    delete(nil);
    int sz = ans.size();
    printf("%d\n",sz);
    while(!ans.empty()){
        printf("%d ",ans.top());
        ans.pop();
    }
    return 0;
}
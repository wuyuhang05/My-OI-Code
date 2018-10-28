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
    struct Edge *firstEdge;
    LL dist;
    int low,dfn,num;bool vis,used;
}node[MAXN],graph[MAXN],rnode[MAXN];
int cnt;
struct Edge{
    Node *s,*t;
    Edge *next;LL w;
    int num;
}pool[MAXN<<2],*frog = pool;

Edge *New(Node *s,Node *t,LL w,LL pos){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;ret->num = pos;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,LL w,LL pos){
    node[u].firstEdge = New(&node[u],&node[v],w,pos);
    rnode[v].firstEdge = New(&rnode[v],&rnode[u],w,pos);
}

inline void add1(int u,int v,LL pos){
    graph[u].firstEdge = New(&graph[u],&graph[v],0,pos);
    graph[v].firstEdge = New(&graph[v],&graph[u],0,pos);
}

int N,M,Q,S,T;
#define P std::pair<LL,Node *>
#define MP std::make_pair
inline void dij1(){
    FOR(i,1,N) node[i].dist = LLONG_MAX;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(node[S].dist = 0,&node[S]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        if(v->used) continue;
        v->used = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                q.push(MP(e->t->dist,e->t));
            }
        }
    }
}

inline void dij2(){
    FOR(i,1,N) rnode[i].dist = LLONG_MAX;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(rnode[T].dist = 0,&rnode[T]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        if(v->used) continue;
        v->used = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                q.push(MP(e->t->dist,e->t));
            }
        }
    }
}

inline void build(){
    int cost = node[T].dist;
    FOR(i,1,N){
        for(Edge *e = node[i].firstEdge;e;e = e->next){
            if(node[i].dist+rnode[e->t->num].dist+e->w == cost) add1(i,e->t->num,e->num);
        }
    }
}
std::vector<int> V;
void dfs(Node *v,Edge *fa){
    static int ts = 0;
    v->low = v->dfn = ++ts;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->dfn){
            dfs(e->t,e);
            v->low = std::min(v->low,e->t->low);
            if(e->t->low > v->dfn) V.push_back(e->num);
        }
        else if(e->num != fa->num) v->low = std::min(v->low,e->t->dfn);
    }
}

bool ans[MAXN];

int main(){
    read(N);read(M);read(Q);read(S);read(T);
    FOR(i,1,N) node[i].num = graph[i].num = rnode[i].num = i;
    FOR(i,1,M){
        int u,v,w;read(u);read(v);read(w);
        add(u,v,w,i);
    }
    dij1();dij2();build();
    Edge *nil = (Edge *) malloc (sizeof(Edge));nil->num = -1;
    dfs(&graph[S],nil);
    delete(nil);
    FOR(i,0,(int)V.size()-1){
        ans[V[i]] = true;//DEBUG(V[i]);
    }
    while(Q--){
        int x;read(x);
        puts(ans[x] ? "YES" : "NO");
    }
    return 0;
}
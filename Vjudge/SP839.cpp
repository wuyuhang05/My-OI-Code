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

const int MAXN = 500*32 + 5;

struct Graph{
    int u,v;
}G[MAXN];

struct Node{
    struct Edge *first,*cur;
    int level,num;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int flow,cap;
}pool[MAXN<<2],*frog = pool;

inline Edge *New(Node *s,Node *t,int cap){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,0,cap};
    return ret;
}

inline void add(int u,int v,int cap,int rev=0){
    node[u].first = New(&node[u],&node[v],cap);
    node[v].first = New(&node[v],&node[u],rev);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;

inline bool bfs(Node *s,Node *t){
    FOR(i,0,N){
        node[i].cur = node[i].first;
        node[i].level = 0;
    }
    std::queue<Node *> q;q.push(s);
    s->level = 1;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->first;e;e = e->next){
            if(e->flow < e->cap && !e->t->level){
                e->t->level = v->level + 1;
                if(e->t == t) return true;
                q.push(e->t);
            }
        }
    }
    return false;
}

int dfs(Node *v,Node *t,int limit=LLONG_MAX){
    int flow;
    if(v == t) return limit;
    for(Edge *&e = v->cur;e;e = e->next){
        if(e->flow < e->cap && e->t->level == v->level + 1){
            if((flow = dfs(e->t,t,std::min(limit,e->cap-e->flow)))){
                e->flow += flow;
                e->rev->flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int dinic(){
    int ans = 0,flow;
    while(bfs(&node[S],&node[T])){
        while((flow = dfs(&node[S],&node[T]))){
            ans += flow;
        }
    }
    return ans;
}

int ans[MAXN];

void find(Node *v,int base){
    v->vis = true;
    // DEBUG(v);
    ans[v->num] += base;
    for(Edge *e = v->first;e;e = e->next){
        // DEBUG(e->t);DEBUG(e->t->num);
       // DEBUG(e->t->num);DEBUG(e->flow);DEBUG(e->cap);DEBUG(e->t->vis);
        if(e->flow < e->cap && !e->t->vis){
            //DEBUG(e->t->num);
            find(e->t,base);
        }
    }
}

inline void init(){
    CLR(node,0);CLR(pool,0);
    frog = pool;
    FOR(i,0,N) node[i].num = i;
}

int n,m,t,res;
int x[MAXN],y[MAXN];

inline void Solve(){
    init();CLR(ans,0);CLR(x,0);CLR(y,0);CLR(G,0);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m) scanf("%lld%lld",&G[i].u,&G[i].v);
    scanf("%lld",&t);
    FOR(i,1,t) scanf("%lld%lld",x+i,y+i);
    int base = 1;
    N = n + 1;S = 0,T = N;
    FOR(len,0,30){
        init();
        FOR(i,1,m) add(G[i].u,G[i].v,1,1);
        FOR(i,1,t){
            if(y[i]&base) add(S,x[i],LLONG_MAX);
            else add(x[i],T,LLONG_MAX);
        }
        dinic();
        find(&node[S],base);
        base <<= 1;
    }
    FOR(i,1,n) printf("%lld\n",ans[i]);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
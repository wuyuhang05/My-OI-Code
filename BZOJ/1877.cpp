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
const int MAXN = 5000+5;
const int MAXM = 50000+5;

struct Node{
    struct Edge *first,*pre;
    int dist;bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow,cost;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int cap,int cost){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,cap,0,cost};
    return ret;
}

inline void add(int u,int v,int cap,int cost){
    node[u].first = New(&node[u],&node[v],cap,cost);
    node[v].first = New(&node[v],&node[u],0,-cost);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;
int cot;
inline bool spfa(Node *s,Node *t){
    FOR(i,0,N+5){
        node[i].dist = INT_MAX;node[i].pre = NULL;
        node[i].vis = false;
    }
    std::queue<Node *> q;q.push(s);
    s->vis = true;s->dist = 0;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->vis = false;
        // DEBUG(++cot);
        for(Edge *e = v->first;e;e = e->next){
            //DEBUG(e);
            if(e->flow < e->cap && e->t->dist > v->dist + e->cost){
                e->t->dist = v->dist + e->cost;
                e->t->pre = e;
                if(!e->t->vis){
                    e->t->vis = true;
                    q.push(e->t);
                }
            }
        }
    }
    return t->pre;
}

int maxFlow,minCost;

inline void work(){
    while(spfa(&node[S],&node[T])){
        int flow = INT_MAX;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            flow = std::min(flow,v->pre->cap-v->pre->flow);
        }
        maxFlow += flow;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            v->pre->flow += flow;
            v->pre->rev->flow -= flow;
            minCost += flow * v->pre->cost;
        }
    }
}

int n,m;

signed main(){
    //freopen("3.in","r",stdin);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        if(u == 1) add(1,v,1,w);
        else if(v == n) add(u+n,v,1,w);
        else add(u+n,v,1,w);
    }
    S = 1,T = n;N = (n<<1);
    FOR(i,2,n-1) add(i,i+n,1,0);
    work();
    printf("%lld %lld\n",maxFlow,minCost);
    return 0;
}
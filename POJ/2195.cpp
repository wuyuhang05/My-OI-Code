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

const int MAXN = 10000+5;
const int MAXM = 20000+5;

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
    // DEBUG(u);DEBUG(v);DEBUG(cost);
    node[u].first = New(&node[u],&node[v],cap,cost);
    node[v].first = New(&node[v],&node[u],0,-cost);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;

inline bool spfa(Node *s,Node *t){
    FOR(i,0,N){
        node[i].pre = NULL;node[i].vis = false;
        node[i].dist = INT_MAX;
    }
    std::queue<Node *> q;q.push(s);
    s->dist = 0;s->vis = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->vis = false;
        for(Edge *e = v->first;e;e = e->next){
            if(e->flow < e->cap && e->t->dist > v->dist + e->cost){
                e->t->dist = v->dist + e->cost;
                e->t->pre = e;
                if(!e->t->vis) q.push(e->t),e->t->vis = true;
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
            minCost += flow*v->pre->cost;
        }
    }
}

int n,m;
#define P std::pair<int,int>
#define MP std::make_pair

std::vector<P> peo,hou;

inline void init(){
    frog = pool;CLR(node,0);
    peo.clear();hou.clear();
    maxFlow = minCost = 0;
}

char str[MAXM];

inline void Solve(){
    init();
    FOR(i,1,n){
        scanf("%s",str+1);
        FOR(j,1,m){
            if(str[j] == 'm') peo.push_back(MP(i,j));
            if(str[j] == 'H') hou.push_back(MP(i,j));
        }
    }
    int sz = peo.size();
    FOR(i,0,sz-1){
        FOR(j,0,(int)hou.size()-1){
            add(i+1,sz+j+1,1,std::abs(peo[i].first-hou[j].first)+std::abs(peo[i].second-hou[j].second));
        }
    }
    S = 0,T = sz+(int)hou.size()+1;N = T;
    FOR(i,1,sz) add(S,i,1,0);
    FOR(i,1,(int)hou.size()) add(i+sz,T,1,0);
    work();
    printf("%d\n",minCost);
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        if(!n && !m) return 0;
        Solve();
    }
    return 0;
}
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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;
const int MAXM = 3000+5;

struct Node{
    struct Edge *firstEdge;
    int dist;bool inQueue;
    int num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
    int w;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    if(w >= 0) node[v].firstEdge = New(&node[v],&node[u],w);
}

int limit;
int N,M;

inline bool spfa(){
    std::queue<Node *> q;
    FOR(i,1,N){
        node[i].inQueue = false;
        node[i].dist = INT_MAX;
    }
    q.push(&node[0]);node[0].inQueue = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        DEBUG(v->num);DEBUG(v->dist);DEBUG(limit);
        v->inQueue = false;
        if(v->dist < limit) return true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                if(!e->t->inQueue){
                    q.push(e->t);
                    e->t->inQueue = true;
                }
            }
        }
    }   
    return false;
}

inline void Solve(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) node[i].num = i;
    FOR(i,1,M){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        limit = w < 0 ? limit+w : limit;
    }
    FOR(i,1,N) add(0,i,0);
    bool ans = spfa();
    if(ans) puts("YE5");
    else puts("N0");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

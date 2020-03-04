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
const int MAXM = 50000+5;
const int MAXK = 10+5;

struct Node{
    struct Edge *firstEdge;
    int dist[MAXK];
    bool used[MAXK];
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,w,s->firstEdge};
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
}

int N,M,K,S,T;
#define P std::pair<int,Node *>
#define MP std::make_pair

inline void dij(){
    FOR(i,1,N) FOR(j,0,K) node[i].dist[j] = INT_MAX;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q[MAXK];
    q[0].push(MP(0,&node[S]));
    node[S].dist[0] = 0;
    FOR(i,0,K){
        while(!q[i].empty()){
            Node *v = q[i].top().second;q[i].pop();
            if(v->used[i]) continue;
            v->used[i] = true;
            for(Edge *e = v->firstEdge;e;e = e->next){
                if(e->t->dist[i] > v->dist[i] + e->w){
                    e->t->dist[i] = v->dist[i] + e->w;
                    q[i].push(MP(e->t->dist[i],e->t));
                }
            }
            if(i == K) continue;
            for(Edge *e = v->firstEdge;e;e = e->next){
                if(e->t->dist[i+1] > v->dist[i]){
                    e->t->dist[i+1] = v->dist[i];
                    q[i+1].push(MP(e->t->dist[i+1],e->t));
                }
            }
        }
    }
}

int main(){
    scanf("%d%d%d%d%d",&N,&M,&K,&S,&T);
    FOR(i,1,M){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dij();
    int ans = INT_MAX;
    FOR(i,0,K) ans = std::min(ans,node[T].dist[i]);
    printf("%d\n",ans);
    return 0;
}
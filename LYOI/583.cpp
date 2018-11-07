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
#define P std::pair<int,Node *>
#define MP std::make_pair
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500 + 5;
const int MAXM = 2000 + 5;

struct Node{
    int dist[MAXN],used[MAXN];
    struct Edge *firstEdge;
}node[MAXN];

struct Edge{
    Node *s,*t;int w;
    Edge *next;
    int type;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w,int type){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->type = type;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w,int type=0){
    node[u].firstEdge = New(&node[u],&node[v],w,type);
}


std::priority_queue<P,std::vector<P>,std::greater<P> > q[MAXN];
int N,M,Q,K;

void dijkstra(){
    FOR(i,1,N) CLR(node[i].dist,0x3f);
    q[0].push(MP(node[1].dist[0]=0,&node[1]));
    FOR(k,0,K){
        while(!q[k].empty()){
            Node *v = q[k].top().second;q[k].pop();
            if(v->used[k]) continue;
            v->used[k] = true;
            for(Edge *e = v->firstEdge;e;e = e->next){
                if(e->type) continue;
                if(e->t->dist[k] > v->dist[k] + e->w){
                    e->t->dist[k] = v->dist[k] + e->w;
                    q[k].push(MP(e->t->dist[k],e->t));
                }
            }
            if(k < K)
                for(Edge *e = v->firstEdge;e;e = e->next){
                    if(!e->type) continue;
                    if(e->t->dist[k+1] > v->dist[k] + e->w){
                        e->t->dist[k+1] = v->dist[k] + e->w;
                        q[k+1].push(MP(e->t->dist[k+1],e->t));
                    }
                }
        }
    }
}

int main(){
    scanf("%d%d%d%d",&N,&M,&Q,&K);K = std::min(K,N-1);
    FOR(i,1,M){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    FOR(i,1,Q){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w,1);
    }
    dijkstra();
    int ans = INT_MAX;
    FOR(i,0,K) ans = std::min(ans,node[N].dist[i]);
    if(ans >= 0x3f3f3f3f) puts("-1");
    else printf("%d\n",ans);
    return 0;
}

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
const int MAXM = 200000 + 5;

int N,M,K,P;

struct Node{
    struct Edge *firstEdge;
    int dist,num;
    bool used;
}node[MAXN],rnode[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;ret->w = w;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    rnode[v].firstEdge = New(&rnode[v],&rnode[u],w);
}

#define P std::pair<int,Node *>
#define MP std::make_pair

inline void dij(){
    std::priority_queue<P,std::vector<P>,std::greater<P> >q;
    FOR(i,1,N){
        node[i].num = rnode[i].num = i;
        rnode[i].dist = INT_MAX;
        rnode[i].used = false;
    }
    q.push(MP(rnode[N].dist=0,&rnode[N]));
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

int f[MAXN][100];
int vis[MAXN][100];
int ha;

int dfs(Node *v,int k){
    if(vis[v->num][k]) return -1;
    if(f[v->num][k]) return f[v->num][k];
    vis[v->num][k] = true;
    f[v->num][k] = (v->num == N) ? 1 : 0;
    for(Edge *e = v->firstEdge;e;e = e->next){
        int t = rnode[e->t->num].dist+e->w-rnode[v->num].dist;
        if(t <= k && t >= 0){
            int res = dfs(e->t,k-t);
            if(res == -1) return f[v->num][k] = -1;
            f[v->num][k] = (f[v->num][k] + res)%ha;
        }
    }
    vis[v->num][k] = false;
    return f[v->num][k];
}

inline void Solve(){
    CLR(f,0);CLR(vis,false);
    frog = pool;
    scanf("%d%d%d%d",&N,&M,&K,&ha);
    CLR(node,0);CLR(rnode,0);
    FOR(i,1,M){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    dij();
    int ans = dfs(&node[1],K);
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
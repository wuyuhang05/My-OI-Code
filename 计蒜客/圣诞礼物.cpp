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

const int MAXN = 1000+5;
const int MAXM = 200000+5;

struct Node{
    struct Edge *first,*cur;
    int level;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow;
}pool[MAXM<<1],*frog = pool;

LL f[MAXN][MAXN];

struct People{
    int c,t;

    bool operator < (const People &other) const {
        return t + f[c][other.c] <= other.t;
    }
}p[MAXM];

Edge *New(Node *s,Node *t,int cap){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,cap,0};
    return ret;
}

inline void add(int u,int v,int cap){
    node[u].first = New(&node[u],&node[v],cap);
    node[v].first = New(&node[v],&node[u],0);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;

bool bfs(Node *s,Node *t){
    FOR(i,0,N){
        node[i].cur = node[i].first;
        node[i].level = 0;
    }
    std::queue<Node *> q;
    q.push(s);s->level = 1;
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

int dfs(Node *v,Node *t,int limit=INT_MAX){
    if(v == t) return limit;
    int flow;
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

int dinic(){
    int ans=0,flow;
    while(bfs(&node[S],&node[T])){
        while((flow = dfs(&node[S],&node[T]))){
            ans += flow;
        }
    }
    return ans;
}
int n,m,q;
inline void Floyd(){
    FOR(k,1,n){
        FOR(i,1,n){
            FOR(j,1,n){
                f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
            }
        }
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) FOR(j,1,n) f[i][j] = LLONG_MAX;
    FOR(i,1,n) f[i][i] = 0;
    FOR(i,1,m){
        int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
        u++;v++;
        f[u][v] = f[v][u] = w;
    }
    FOR(i,1,q) scanf("%d%d",&p[i].c,&p[i].t),p[i].c++;
    Floyd();
    FOR(i,1,q) FOR(j,1,q) if(i != j && p[i] < p[j]) add(i,n+j,1);
    S = 0,T = 2*n+1;N = T;
    FOR(i,1,n) add(S,i,1),add(i+n,T,1);
    printf("%d\n",n-dinic()-1);
    return 0;
}
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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define EFOR(i,v) for(Edge *i = v->firstEdge;i;i = i->next)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000 + 5;

struct Node{
    struct Edge *firstEdge;
    int depth,num;
    LL dist;
    bool used,vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXN*2],*frog = pool;

struct Train{
    int u,v;
    LL ts;

    bool operator < (const Train &other) const {
        if(ts == other.ts) return node[u].depth < node[other.u].depth;
        return ts < other.ts;
    }
}t[MAXN];

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

float log2N;
int N,M;
int f[MAXN][50];

inline void init(){
    CLR(f,-1);
    FOR(i,1,N){
        node[i].num = i;
        node[i].depth = 0;
        node[i].vis = false;
        node[i].used = false;
        node[i].dist = 0;
    }
    node[1].depth = 1;
    node[1].used = true;
    log2N = log2(N) + 1;
}

void dfs(Node *v){
    FOR(i,1,log2N){
        if(v->depth <= (1 << i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    EFOR(e,v){
        if(!e->t->used){
            e->t->used = true;
            e->t->depth = v->depth + 1;
            e->t->dist = v->dist + e->w;
            f[e->t->num][0] = v->num;
            dfs(e->t);
        }
    }
}

int lca(int x,int y){
    int dx = node[x].depth,dy = node[y].depth;
    if(dx != dy){
        if(dx < dy){
            std::swap(dx,dy);
            std::swap(x,y);
        }
        int d = dx-dy;
        FOR(i,0,log2N){
            if((1 << i) & d) x = f[x][i];
        }
    }
    if(x == y) return x;
    RFOR(i,log2N,0){
        if(node[f[x][i]].depth < 0) continue;
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i];y = f[y][i];
    }
    return f[x][0];
}

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N-1){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    init();
    dfs(&node[1]);
    FOR(i,1,M){
        int u,v;
        LL ti;
        scanf("%d%d%lld",&u,&v,&ti);
        int l = lca(u,v);
        t[i] = (Train){l,v,ti + node[u].dist - 2 * node[l].dist};
    }
    std::sort(t + 1,t + M + 1);
    node[1].vis = true;
    FOR(i,1,M){
        if(node[t[i].u].vis){
            int v = t[i].v;
            while(!node[v].vis){
                node[v].vis = 1;
                v = f[v][0];
            }
        }
    }
    int ans = 0;
    FOR(i,1,N) ans += (node[i].vis) ? 1 : 0;
    printf("%d\n",ans);
    FOR(i,1,N)
        if(node[i].vis)
            printf("%d ",i);
    return 0;
}

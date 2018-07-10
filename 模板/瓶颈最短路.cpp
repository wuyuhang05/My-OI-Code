#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

using std::max;
using std::sort;
const int MAXN = 100000 + 5;

int N,M,Q;
float log2N;

struct Graph{
    int u,v,w;

    bool operator < (const Graph &other) const{
        return w < other.w;
    }
}e[MAXN * 2];

struct Node{
    int num,depth;
    bool used;
    struct Edge *firstEdge;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXN * 2],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

int fa[MAXN];

int find(int x){
    return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Kruskal(){
    for(int i = 1;i <= M;i++)
        fa[i] = i;
    sort(e + 1,e + M + 1);
    int cnt = 0;
    for(int i = 1;i <= M;i++){
        int fx = find(e[i].u),fy = find(e[i].v);
        if(fx == fy) continue;
        add(e[i].u,e[i].v,e[i].w);
        fa[fy] = fx;
        if(++cnt == N - 1) break;
    }
}

int f[MAXN][50 + 5],maxv[MAXN][50 + 5];

inline void init(){
    for(int i = 1;i <= N;i++){
        node[i].depth = 0;
        node[i].num = i;
        node[i].used = false;
    }
    log2N = log(N)/log(2);
}

void dfs(Node *v){
    for(int i = 1;i <= log2N;i++){
        if(v->depth <= (1<<i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
        maxv[v->num][i] = max(maxv[v->num][i-1],maxv[f[v->num][i-1]][i-1]);
    }
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->used){
            e->t->used = true;
            e->t->depth = v->depth + 1;
            maxv[e->t->num][0] = e->w;
            f[e->t->num][0] = v->num;
            dfs(e->t);
        }
    }
}

int query(int u,int v){
    int ret = INT_MIN;
    if(node[u].depth < node[v].depth)
        std::swap(u,v);
    for(int j = log2N;j >= 0;j--){
        if(node[u].depth - (1<<j) >= node[v].depth){
            ret = max(ret,maxv[u][j]); 
            u = f[u][j];
        }
    }
    if(u == v) return ret;
    for(int j = log2N;j >= 0;j--){
        if(f[u][j] && f[u][j] != f[v][j]){
            ret = max(ret,max(maxv[u][j],maxv[v][j]));
            u = f[u][j];
            v = f[v][j];
        }
    }
    return max(ret,max(maxv[u][0],maxv[v][0]));
}

int main(){
    scanf("%d%d%d",&N,&M,&Q);
    for(int i = 1;i <= M;i++){
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    Kruskal();
    init();
    dfs(&node[(1 + N) >> 1]);
    while(Q--){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    getchar();getchar();
    return 0;
}
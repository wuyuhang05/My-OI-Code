#include <iostream>
#include <cstdio>
#include <stack>
#include <cstring>
#include <queue>

const int MAXN = 100000 + 5;
const int MAXM = 500000 + 5;

struct Node;
struct Edge;

int N,M;

Edge *New_Graph(Node *,Node *);
Edge *New_Scc(Node *,Node *);

int in[MAXN],tot,dist[MAXN],dfn[MAXN],low[MAXN],cor[MAXN];
int mincost[MAXN],maxcost[MAXN],ans[MAXN];

struct Node{
    int num;
    bool instack;
    Edge *firstEdge;
}node[MAXN],scc[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}Graph_pool[MAXM * 2],*Graph_frog = Graph_pool,Scc_pool[MAXM * 2],*Scc_frog = Scc_pool;

Edge *New_Graph(Node *u,Node *v){
    Edge *ret = ++Graph_frog;
    ret->s = u;ret->t = v;
    ret->next = u->firstEdge;
    return ret;
}

Edge *New_Scc(Node *u,Node *v){
    Edge *ret = ++Scc_frog;
    ret->s = u;ret->t = v;
    ret->next = u->firstEdge;
    return ret;
}

inline void add_Graph(int u,int v){
    node[u].firstEdge = New_Graph(&node[u],&node[v]);
}

inline void add_Scc(int u,int v){
    scc[u].firstEdge = New_Scc(&scc[u],&scc[v]);
}

void init(){
    for(int i = 1;i <= N;i++){
        scc[i].num = node[i].num = i;
        node[i].instack = false;
    }
    memset(mincost,0x3f,sizeof(mincost));
}

std::stack<Node *> s;
int timer = 0;

inline void tarjan(Node *v){
    dfn[v->num] = low[v->num] = ++timer;
    s.push(v);
    v->instack = true;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!dfn[e->t->num]){
            tarjan(e->t);
            low[v->num] = std::min(low[v->num],low[e->t->num]);
        }
        else
            if(e->t->instack)
                low[v->num] = std::min(low[v->num],dfn[e->t->num]);
    }
    if(dfn[v->num] == low[v->num]){
        Node *r; ++tot;
        do{
            r = s.top();s.pop();
            r->instack = false;
            cor[r->num] = tot;
            maxcost[tot] = std::max(maxcost[tot],dist[r->num]);
            mincost[tot] = std::min(mincost[tot],dist[r->num]);
        }while(r != v);
    }
}

void Rebuild(){
    for(int i = 1;i <= N;i++){
        for(Edge *e = node[i].firstEdge;e;e = e->next){
            if(cor[i] == cor[e->t->num] || cor[e->t->num] == cor[1] || cor[N] == cor[i])
                continue;
            add_Scc(cor[e->t->num], cor[i]);
            ++in[cor[i]];
        }
    }
}

void topsort(){
    std::queue<Node *> q;
    for(int i = 1;i <= tot;i++)
        if(!in[i] && i != cor[N])
            q.push(&scc[i]);
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--in[e->t->num])
                q.push(e->t);
        }
    }
    q.push(&scc[cor[N]]);
    while(!q.empty()){
        Node *v = q.front();q.pop();
        ans[v->num] = std::max(ans[v->num],maxcost[v->num] - mincost[v->num]);
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--in[e->t->num])
                q.push(e->t);
            maxcost[e->t->num] = std::max(maxcost[v->num],maxcost[e->t->num]);
            ans[e->t->num] = std::max(ans[e->t->num],ans[v->num]);
        }
    }
}

int main(){
    scanf("%d%d",&N,&M);
    init();
    for(int i = 1;i <= N;i++)
        scanf("%d",&dist[i]);
    for(int u,v,opt,i = 1;i <= M;i++){
        scanf("%d%d%d",&u,&v,&opt);
        add_Graph(u,v);
        if(opt == 2)
            add_Graph(v,u);
    }
    for(int i = 1;i <= N;i++)
        if(!dfn[i])
            tarjan(&node[i]);
    Rebuild();
    topsort();
    printf("%d\n",ans[cor[1]]);
    return 0;
}

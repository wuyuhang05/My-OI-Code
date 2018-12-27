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

const int MAXN = 200+5;
const int MAXM = MAXN*MAXN;

struct Node{
    struct Edge *first,*cur;
    int level;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow;
}pool[MAXM<<1],*frog = pool;

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
    for(Edge *&e = v->first;e;e = e->next){
        if(e->flow < e->cap && e->t->level == v->level + 1){
            if((flow = dfs(e->t,t,std::min(limit,e->cap-e->flow)))){
                e->flow += flow;e->rev->flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

int dinic(){
    int flow,ans = 0;
    while(bfs(&node[S],&node[T]))
        while((flow = dfs(&node[S],&node[T])))
            ans += flow;
    return ans;
}

int n,m;
int in[MAXN],out[MAXN],tot;

inline void init(){
    CLR(node,0);CLR(pool,0);frog = pool;
    tot = 0;CLR(in,0);CLR(out,0);
}

bool build(){
    S = 0,T = n+1;N = T;
    FOR(i,1,n){
        if((in[i] + out[i])&1) return false;
        else if(out[i] > in[i]){
            add(S,i,(out[i]-in[i])/2);
            tot += (out[i]-in[i])/2;
        }
        else{
            add(i,T,(in[i]-out[i])/2);
        }
    }
    return true;
}

inline void Solve(){
    init();
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,f;
        scanf("%d%d%d",&u,&v,&f);
        in[v]++;out[u]++;
        if(!f)
            add(u,v,1);
    }
    if(!build()){
        puts("impossible");
        return;
    }
    if(dinic() >= tot) puts("possible");
    else puts("impossible");
}

int main(){
    srand(19260817);
    int T;scanf("%d",&T);
    //int T = 1;
    while(T--) Solve();
    return 0;
}
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

const int MAXN = 2000+5;

struct Node{
    struct Edge *first,*cur;
    int level;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow;
}pool[MAXN<<1],*frog = pool;

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

int N,M;

bool bfs(Node *s,Node *t){
    FOR(i,1,N){
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
    while(bfs(&node[1],&node[N]))
        while((flow = dfs(&node[1],&node[N])))
            ans += flow;
    return ans;
}

inline void init(){
    CLR(node,0);frog = pool;
}

int cnt = 0;

inline void Solve(){
    init();scanf("%d%d",&N,&M);
    FOR(i,1,M){
        int u,v,c;scanf("%d%d%d",&u,&v,&c);
        add(u,v,c);
    }
    printf("Case %d: %d\n",++cnt,dinic());
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
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
const int MAXM = 1000000+5;

struct Node{
    struct Edge *first,*cur;
    int level,num;
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
    std::queue<Node *> q;q.push(s);
    s->level = 1;
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
    int flow;
    if(v == t) return limit;
    for(Edge *&e = v->cur;e;e = e->next){
        if(e->flow < e->cap && e->t->level == v->level + 1)
            if((flow = dfs(e->t,t,std::min(limit,e->cap-e->flow)))){
                e->flow += flow;
                e->rev->flow -= flow;
                return flow;
            }
    }
    return 0;
}

int dinic(){
    int ret = 0,flow = 0;
    while(bfs(&node[S],&node[T])){
        while((flow = dfs(&node[S],&node[T]))) ret += flow;
    }
    return ret;
}

int n,m,sum;
int a[MAXN],b[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),sum += a[i];
    FOR(i,1,m) scanf("%d",b+i);
    S = 0,T = n+m+1;
    N = T;
    FOR(i,1,n) node[i].num = i;
    FOR(i,1,m) node[i+n].num = i;
    FOR(i,1,n) add(S,i,a[i]);
    FOR(i,1,m) add(n+i,T,b[i]);
    FOR(i,1,n) FOR(j,1,m) add(i,n+j,1);
    int ans=dinic();
    //DEBUG(ans);DEBUG(sum);
    if(ans != sum){
        puts("0");return 0;
    }
    puts("1");
    FOR(i,1,n){
        for(Edge *e = node[i].first;e;e = e->next){
            if(e->cap == e->flow)
                printf("%d ",e->t->num);
        }
        puts("");
    }
    return 0;
}
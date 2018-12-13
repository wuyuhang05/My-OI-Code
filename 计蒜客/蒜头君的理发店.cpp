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
    struct Edge *first,*pre;
    int dist;bool inq;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int flow,cap,cost;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int cap,int cost){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,0,cap,cost};
    return ret;
}

inline void add(int u,int v,int cap,int cost){
    node[u].first = New(&node[u],&node[v],cap,cost);
    node[v].first = New(&node[v],&node[u],0,-cost);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;

inline bool spfa(Node *s,Node *t){
    FOR(i,0,N){
        node[i].dist = INT_MAX;
        node[i].inq = false;
        node[i].pre = NULL;
    }
    std::queue<Node *> q;
    q.push(s);s->dist = 0;s->inq = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->inq = false;
        for(Edge *e = v->first;e;e = e->next){
            //DEBUG(e->t->dist);DEBUG(v->dist);DEBUG(e->cost);
            if(e->flow < e->cap && e->t->dist > v->dist + e->cost){
                e->t->dist = v->dist + e->cost;
                e->t->pre = e;
                if(!e->t->inq){
                    e->t->inq = true;
                    q.push(e->t);
                }
            }
        }
    }
    return t->pre != NULL;
}

inline int mincost(){
    int ret=0;
    while(spfa(&node[S],&node[T])){
        int flow = INT_MAX;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            flow = std::min(flow,v->pre->cap - v->pre->flow);
        }
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            v->pre->flow += flow;
            v->pre->rev->flow -= flow;
            ret += flow*v->pre->cost;
        }
    }
    return ret;
}

int n,m;
int t[MAXN][MAXN];

inline int getp(int x,int y){
    return (x-1)*m+y;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m) FOR(j,1,n) scanf("%d",&t[i][j]);
    FOR(i,1,n){
        FOR(j,1,m){
            FOR(k,1,m){
                add(getp(i,j),getp(n,m)+k,1,t[k][i]*j);
            }
        }
    }
    S = 0;T = getp(n,m)+m+1;
    N = T;
    FOR(i,1,getp(n,m)) add(S,i,1,0);
    FOR(i,1,m) add(getp(n,m)+i,T,1,0);
    printf("%.2f\n",1.0*mincost() / m);
    return 0;
}
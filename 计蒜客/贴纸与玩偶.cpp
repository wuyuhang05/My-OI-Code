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
const int MAXM = 10000+5;

struct Node{
    struct Edge *first,*pre;
    int dist;bool inq;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow,cost;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t,int cap,int cost){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,cap,0,cost};
    return ret;
}

int N,M,S,T;

inline void add(int u,int v,int cap,int cost){
    node[u].first = New(&node[u],&node[v],cap,cost);
    node[v].first = New(&node[v],&node[u],0,-cost);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

bool spfa(Node *s,Node *t){
    FOR(i,0,N){
        node[i].dist = INT_MAX;
        node[i].inq = false;
        node[i].pre = NULL;
    }
    std::queue<Node *> q;
    q.push(s);s->inq = true;s->dist = 0;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->inq = false;
        for(Edge *e = v->first;e;e = e->next){
            if(e->flow < e->cap && e->t->dist > v->dist + e->cost){
                e->t->dist = v->dist + e->cost;
                e->t->pre = e;
                if(!e->t->inq){
                    q.push(e->t);e->t->inq = true;
                }
            }
        }
    }
    return t->pre != NULL;
}

inline int mincost(){
    int ret = 0;
    while(spfa(&node[S],&node[T])){
        int flow = INT_MAX;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            flow = std::min(flow,v->pre->cap-v->pre->flow);
        }
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            v->pre->flow += flow;
            v->pre->rev->flow -= flow;
            ret += v->pre->cost*flow;
        }
    }
    return ret;
}

int a[MAXN],b[MAXN];
int h[MAXN][MAXM];
int n,m;

int work(int flag){
    CLR(node,0);CLR(pool,0);frog = pool;
    S = 0,T = n+m+1;
    N = n+m+1;
    FOR(i,1,n) add(S,i,a[i],0);
    FOR(i,1,m) add(n+i,T,b[i],0);
    FOR(i,1,n){
        FOR(j,1,m){
            add(i,n+j,INT_MAX,h[i][j]*flag);
        }
    }
    return mincost()*flag;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i);
    FOR(i,1,m) scanf("%d",b+i);
    FOR(i,1,n) FOR(j,1,m) scanf("%d",&h[i][j]);
    printf("%d\n",work(1));
    printf("%d\n",work(-1));
    return 0;
}
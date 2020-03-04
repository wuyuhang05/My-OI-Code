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

const int MAXN = 5000+5;
const int MAXM = 50000+5;

inline char nc(){
    #define SIZE 100000
    static char buf[SIZE],*p1 = buf+SIZE,*pend = buf+SIZE;
    if(p1 == pend){
        p1 = buf;pend = buf+fread(buf,1,SIZE,stdin);
        if(p1 == pend) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 1;
    char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = -1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    x *= flag;
}

struct Node{
    struct Edge *first,*pre;
    int dist,h;bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int flow,cap,cost;
}pool[(MAXM<<1)+3],*frog = pool;

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

#define P std::pair<int,Node *>
#define MP std::make_pair

int N,M,S,T;
int maxFlow,minCost;

bool spfa(Node *s,Node *t){
    FOR(i,1,N) node[i].vis = false,node[i].dist = INT_MAX,node[i].pre = NULL;
    s->vis = true;s->dist = 0;
    std::queue<Node *> q;q.push(s);
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->vis = false;
        for(Edge *e = v->first;e;e = e->next){
            if(e->flow < e->cap){
                if(e->t->dist > v->dist + e->cost){
                    e->t->dist = v->dist + e->cost;
                    e->t->pre = e;
                    if(!e->t->vis) q.push(e->t),e->t->vis = true;
                }
            }
        }
    }
    return t->pre != NULL;
}

inline void work(){
    while(spfa(&node[S],&node[T])){
        int flow = INT_MAX;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            flow = std::min(flow,v->pre->cap-v->pre->flow);
        }
        maxFlow += flow;
        for(Node *v = &node[T];v != &node[S];v = v->pre->s){
            v->pre->flow += flow;
            v->pre->rev->flow -= flow;
            minCost += v->pre->cost * flow;
        }
    }
}

int main(){
    //freopen("./LG/testdata.in","r",stdin);
    read(N);read(M);read(S);read(T);
    // DEBUG(N);
    while(M--){
        int u,v,cap,cost;
        read(u);read(v);read(cap);read(cost);
        add(u,v,cap,cost);
    }
    work();
    printf("%d %d\n",maxFlow,minCost);
    return 0;
}
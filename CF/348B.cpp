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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

struct Node{
    struct Edge *firstEdge;
    int dist,ans,lm;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN*2],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

inline int gcd(int x,int y){
    if(!y) return x;
    return gcd(y,x%y);
}

inline int lcm(int x,int y){
    return (x*y)/gcd(x,y);
}

int N;

void dfs(Node *v,Node *fa){
    v->vis = true;
    int size = 0;DEBUG(v);DEBUG(fa);
    for(Edge *e = v->firstEdge;e;e = e->next){
        // if(e->t == fa) continue;
        if(e->t->vis) continue;
        dfs(e->t,v);
        if(!size){
            v->lm = e->t->lm;
            v->ans = e->t->ans;
        }
        else{
            if(v->lm < INT_MAX){
                v->lm = lcm(v->dist,e->t->lm);
                v->ans = std::min(v->ans,e->t->ans)/v->lm*v->lm;
            }
        }
        size++;
    }
    if(!size){
        v->lm = 1;v->ans = v->dist;
    }
    else{
        v->ans *= size;
        if(v->lm < INT_MAX) v->lm *= size;
    }
}

LL sum;

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d",&node[i].dist);
        sum += node[i].dist;
    }
    FOR(i,1,N-1){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs(&node[1],&node[0]);
    printf("%d\n",sum-node[1].ans);
    return 0;
}
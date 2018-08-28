//一题多解
//二分
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <queue>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000 + 5;
const int MAXM = 2 * MAXN + 5;

int N,M,S,T;


struct Node{
    struct Edge *firstEdge;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM * 2],*frog = pool;

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

bool check(int k){
    for(int i = 1;i <= N;i++) node[i].vis = false;
    std::queue<Node *> q;
    q.push(&node[S]);
    while(!q.empty()){
        Node *v = q.front();
        q.pop();
        v->vis = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!e->t->vis && e->w <=k){
                q.push(e->t);
                if(e->t == &node[T]) return true;
            }
        }
    }
    return false;
}

int main(){
    int L = INT_MAX,R = INT_MIN;
    scanf("%d%d%d%d",&N,&M,&S,&T);
    for(int u,v,w,i = 1;i <= M;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
        L = std::min(L,w);
        R = std::max(R,w);
    }
    while(L < R){
        int mid = (L + R) >> 1;
        if(check(mid)) R = mid;
        else L = mid + 1;
    }
    printf("%d\n",L);
    return 0;
}
//最小生成树
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 10000 + 5;
const int MAXM = MAXN * 2 + 5;

int N,M,S,T;
int ans;

struct Edge{
    int u,v,w;
    
    bool operator < (const Edge &other) const{
        return w < other.w;
    }
}e[MAXM];

int f[MAXN];

int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

void Kruskal(){
    int cnt = 0;
    for(int i = 1;i <= M;i++){
        int fu = find(e[i].u),fv = find(e[i].v);
        if(fu == fv) continue;
        ++cnt;
        if(find(S) == find(T)) break;
        ans = e[i].w;
        f[fv] = fu;
        if(cnt == N - 1) break;
    }
}

int main(){
    scanf("%d%d%d%d",&N,&M,&S,&T);
    for(int i = 1;i <= N;i++) f[i] = i;
    for(int i = 1;i <= M;i++)
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    std::sort(e + 1,e + M + 1);
    Kruskal();
    printf("%d",ans);
    return 0;
}


#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define ULL unsigned long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

int N,M,K,ha;
int f[MAXN][1000];
bool vis[MAXN][100];
bool alive[MAXN];

struct Node{
    struct Edge *firstEdge;
    int dist,num;
    bool used;
}node1[MAXN],node2[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool1[MAXM],pool2[MAXM],*frog1 = pool1,*frog2 = pool2;

Edge *New1(Node *s,Node *t,int w){
    Edge *ret = ++frog1;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

Edge *New2(Node *s,Node *t,int w){
    Edge *ret = ++frog2;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void Read(int &x){
    char ch = getchar();
    int flag = 1;x = 0;
    for(;!isdigit(ch);ch = getchar())
        if(ch == '-') flag = -1;
    for(;isdigit(ch);ch = getchar())
        x = (x << 1) + (x << 3) + (ch  ^ '0');
    x *= flag;
}

inline void add(int u,int v,int w){
    node1[u].firstEdge = New1(&node1[u],&node1[v],w);
    node2[v].firstEdge = New2(&node2[v],&node2[u],w);
}

void dijkstra(){
    std::priority_queue<std::pair<int,Node*>,std::vector<std::pair<int,Node*> >,std::greater<std::pair<int,Node *> > > q;
    for(int i = 1;i <= N;i++){
        node1[i].dist = INT_MAX;
        node1[i].num = node2[i].num = i;
        node1[i].used = false;
    }
    node1[1].dist = 0;
    node1[1].used = true;
    q.push(std::make_pair(node1[1].dist,&node1[1]));
    while(!q.empty()){
        Node *v = q.top().second;
        q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                if(!e->t->used){
                    e->t->used = true;
                    q.push(std::make_pair(e->t->dist,e->t));
                }
            }
        }
    }
}

void check(){
    std::queue<Node *> q;
    alive[N] = true;
    q.push(&node2[N]);
    while(!q.empty()){
        Node *v = q.front();
        q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!alive[e->t->num]){
                alive[e->t->num] =  true;
                q.push(e->t);
            }
        }
    }
}

int dfs(Node *v,int k){
    if(k < 0) return 0;
    if(vis[v->num][k]) return INT_MIN;
    if(f[v->num][k] != -1) return f[v->num][k];
    vis[v->num][k] = true;
    int ret = 0;
    if(v->num == N) ret++;
    for(Edge *e = v->firstEdge;e;e = e->next){
        int delta = e->t->dist - v->dist;
        if(!alive[e->t->num]) continue;
        int w = dfs(e->t,k - e->w + delta);
        if(w == INT_MIN) return INT_MIN;
        else ret = (ret + w)%ha;
    }
    f[v->num][k] = ret % ha;
    vis[v->num][k] = false;
    return ret;
}

int main(){
    int T;
    Read(T);
    while(T--){
        Read(N);Read(M);Read(K);Read(ha);
        memset(pool1,0,sizeof(pool1));
        memset(pool2,0,sizeof(pool2));
        memset(f,-1,sizeof(f));
        memset(vis,false,sizeof(vis));
        memset(alive,false,sizeof(alive));
        for(int i = 1;i <= N;i++)
            node1[i].firstEdge = node2[i].firstEdge = NULL;
        frog1 = pool1;frog2 = pool2;
        for(int u,v,w,i = 1;i <= M;i++){
            Read(u);Read(v);Read(w);
            add(u,v,w);
        }
        dijkstra();
        check();
        int ans = dfs(&node1[1],K);
        printf("%d\n",(ans == INT_MIN) ? -1 : ans);
    }
    return 0;
}



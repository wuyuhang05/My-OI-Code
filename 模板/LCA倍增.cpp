#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

float log2N;

const int MAXN = 500000 + 5;
const int MAXM = 500000 + 5;

struct Node;
struct Edge;

Edge *New(Node *,Node *);

struct Node{
    int height,num;
    bool used;
    Edge *firstEdge;
}node[MAXN];

int f[MAXN][50 + 5];
int N,M,S;

struct Edge{
    Node *s,*t;
    Edge *next;
}poor[MAXM * 2],*tail = poor;

Edge *New(Node *s,Node *t){
    Edge *ret = ++tail;
    ret->s = s;ret->t = t;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

void Read(int &x){
    x = 0;
    int flag = 1;
    char ch = getchar();
    for(;ch < '0' || ch > '9';ch = getchar())
        if(ch == '-') flag = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar()){
        x = (x << 1) + (x << 3) + ch - '0';
    }
    x *= flag;
}

void init(){
    memset(f,-1,sizeof(f));
    for(int i = 0;i <= N;i++){
        node[i].num = i;
        node[i].used = false;
        node[i].height = 0;
    }
    log2N = log(N) / log(2) + 1;
}

void dfs(Node *v,int h){
    v->height = h;
    for(int i = 1;i <= log2N;i++){
        if(h <= (1 << i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->used){
            e->t->used = true;
            f[e->t->num][0] = v->num;
            dfs(e->t,h + 1);
        }
    }
}

int lca(int x,int y){
    int dx = node[x].height,dy = node[y].height;
    if(dx != dy){
        if(dx < dy){
            std::swap(dx,dy);
            std::swap(x,y);
        }
        int d = dx - dy;
        for(int i = 0;i <= log2N;i++){
            if((1 << i) & d) x = f[x][i];
        }
    }
    if(x == y) return y;
    for(int i = log2N;i >= 0;i--){
        if(node[f[x][i]].height < 0) continue;
        if(f[x][i] == f[y][i]) continue;
        else x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

int main(){
    Read(N);Read(M);Read(S);
    for(int x,y,i = 1;i < N;i++){
        Read(x);Read(y);
        add(x,y);
    }
    init();
    node[S].used = true;
    dfs(&node[S],1);
    while(M--){
        int x,y;
        Read(x);Read(y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}

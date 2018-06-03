#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <stack>

float log2N;

const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;

int N,M,tot;
int f[MAXN][21];
int corsize[MAXN];

struct Node;
struct Tree;
struct Graph_Edge;
struct Tree_Edge;

Graph_Edge *Graph_New(Node *,Node *);
Tree_Edge *Tree_New(Tree *,Tree *);

struct Node{
    int dfn,low,num,cor;
    bool instack;
    Graph_Edge *firstEdge;
}node[MAXN];

struct Tree{
    int height,num;
    bool used;
    Tree_Edge *firstEdge;
}tree[MAXN];

struct Graph_Edge{
    Node *s,*t;
    Graph_Edge *next;
}Graph_poor[MAXM * 2],*Graph_tail = Graph_poor;

struct Tree_Edge{
    Tree *s,*t;
    Tree_Edge *next;
}Tree_poor[MAXM * 2],*Tree_tail = Tree_poor;

Graph_Edge *Graph_New(Node *s,Node *t){
    Graph_Edge *ret = ++Graph_tail;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

Tree_Edge *Tree_New(Tree *s,Tree *t){
    Tree_Edge *ret = ++Tree_tail;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void Graph_add(int u,int v){
    node[u].firstEdge = Graph_New(&node[u], &node[v]);
    node[v].firstEdge = Graph_New(&node[v], &node[u]);
}

inline void Tree_add(int u,int v){
    tree[u].firstEdge = Tree_New(&tree[u], &tree[v]);
    tree[v].firstEdge = Tree_New(&tree[v], &tree[u]);
}

void init(){
    log2N = log(N) / log(2) + 1;
    memset(f,-1,sizeof(f));
    for(int i = 1;i <= N;i++){
        node[i].dfn = node[i].low = tree[i].height = 0;
        node[i].num = tree[i].num = i;
        node[i].instack = tree[i].used = false;
    }
}

int timer = 0;

std::stack<Node *> s;

void tarjan(Node *v,Node *fa){
    v->dfn = v->low = ++timer;
    s.push(v);v->instack = true;
    for(Graph_Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->num != fa->num){
            if(!e->t->dfn){
                tarjan(e->t,v);
                v->low = std::min(e->t->low,v->low);
            }
            else
                if(e->t->instack)
                    v->low = std::min(e->t->dfn,v->low);
        }
    }
    Node *j;
    if(v->low == v->dfn){
        ++tot;
        do{
            j = s.top();s.pop();
            j->instack = false;
            j->cor = tot;
            corsize[j->num]++;
        }while(j != v);
    }
}

void Rebuild(){
    for(int i = 1;i <= N;i++){
        for(Graph_Edge *e = node[i].firstEdge;e;e = e->next){
            if(node[i].cor != e->t->cor)
                Tree_add(i, e->t->num);
        }
    }
}

void dfs(Tree *v,int h){
    v->height = h;
    for(int i = 1;i <= log2N;i++){
        if(h <= (1 << i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    for(Tree_Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->used){
            e->t->used = true;
            f[e->t->num][0] = v->num;
            dfs(e->t,h + 1);
        }
    }
}

int lca(int x,int y){
    int dx = tree[x].height,dy = tree[y].height;
    if(dx != dy){
        if(dx < dy){
            std::swap(x,y);
            std::swap(dx,dy);
        }
        int d = dx - dy;
        for(int i = 0;i <= log2N;i++){
            if((1 << i) & d) x = f[x][i];
        }
    }
    if(x == y) return y;
    for(int i = log2N;i >= 0;i--){
        if(tree[f[x][i]].height < 0) continue;
        if(f[x][i] == f[y][i]) continue;
        else{
            x = f[x][i];
            y = f[y][i];
        }
    }
    return f[x][0];
}

inline void Read(int &x){
    x = 0;
    int flag = 1;
    char ch = getchar();
    for(;ch < '0' || ch > '9';ch = getchar())
        if(ch == '-') flag = -1;
    for(;ch >= '0' && ch <= '9';ch = getchar())
        x = (x << 1) + (x << 3) + ch - '0';
    x *= flag;
}

int t[60 + 5];
void Print(int x) {
    if(x == 0){
        puts("0");
        return;
    }
    if(x < 0){
        putchar('-');
        x = 0 - x;
    }
    while(x)
        t[++t[0]] = x & 1,x >>= 1;
    while(*t) putchar(t[(*t)--]+'0');
    putchar('\n');
}

int main(){
    Read(N);Read(M);
    init();
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        Graph_add(u, v);
    }
    for(int i = 1;i <= N;i++)
        if(!node[i].dfn) tarjan(&node[i],&node[1]);
    Rebuild();
    scanf("%d",&M);
    dfs(&tree[1], 0);
    for(int x,y,i = 1;i <= M;i++){
        scanf("%d%d",&x,&y);
        int l = lca(x,y);
        Print(tree[x].height + tree[y].height - (tree[l].height << 1) + 1);
        //printf("%d",tree[x].height + tree[y].height - (tree[l].height << 1) + 1);
    }
    return 0;
}

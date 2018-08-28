#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
#define add(u,v) node[u].firstEdge = New(&node[u],&node[v])
const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;
struct Node;
struct Edge;
int N,M,cnt;
Node* ts[MAXN];
struct Node{
    int ru,dp;
    bool used;
    Edge *firstEdge;
}node[MAXN];
struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXM],*frog = pool; 
Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
} //内存池
inline void topsort(){
    std::queue<Node *> q;
    for(int i = 1;i <= N;i++)
        if(!node[i].ru){
            q.push(&node[i]);
            ts[++cnt] = &node[i];
        }
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--e->t->ru){
                q.push(e->t);
                ts[++cnt] = e->t;
            }
        }
    }
}
int main(){
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add(u,v);
        node[v].ru++;
    }
    topsort();
    for(int i = 1;i <= N;i++)
        node[i].dp = 1;
    for(int i = 1;i <= N;i++){
        Node *v = ts[i];
        for(Edge *e = v->firstEdge;e;e = e->next){
            e->t->dp = std::max(e->t->dp,v->dp + 1);
        }
    }
    for(int i = 1;i <= N;i++)
        printf("%d\n",node[i].dp);
    return 0;
}

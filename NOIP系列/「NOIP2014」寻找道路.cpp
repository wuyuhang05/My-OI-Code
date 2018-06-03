#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <queue>

const int MAXN = 10000 + 5;
#define INTMAX 0x7fffff

struct Node{
    struct Edge{
        Node *s,*t;
        int w;
        Edge *next;

        Edge(Node *s,Node *t,int w) : s(s), t(t), w(w) {}
    };
    Edge *firstEdge;
    bool inQueue;
    int dist;
}node[MAXN];

inline void add(int u,int v,int w){
    node[u].firstEdge = new Node::Edge(&node[u],&node[v],w);
}

int spfa(int s,int t,int N){
    for(int i = 1;i <= N;i++){
        node[i].dist = INTMAX;
        node[i].inQueue = false;
    }
    std::queue<Node *> q;
    q.push(&node[s]);
    node[s].inQueue = false;
    node[s].dist = 0;
    while(!q.empty()){
        Node *v = q.front();
        q.pop();
        v->inQueue = false;
        for(Node::Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                q.push(e->t);
                e->t->inQueue = true;
            }
        }
    }
    return (node[t].dist == INTMAX) ? -1 : node[t].dist;
}

int main(){
    int N,M,S,T;
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add(v,u,1);
    }
    scanf("%d%d",&S,&T);
    printf("%d",spfa(T,S,N));
    getchar();getchar();
    return 0;
}

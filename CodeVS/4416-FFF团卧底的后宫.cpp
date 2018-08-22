#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <climits>

const int MAXN = 1000 + 5;

int N,M,K;

struct Node{
    int dist;
    int count;
    bool inQueue;
    struct Edge{
        Node *s,*t;
        int w;
        Edge *next;

        Edge(Node *s,Node *t,int w) : s(s), t(t), w(w), next(s->firstEdge) {}
    };
    Edge *firstEdge;
}node[MAXN];

inline void add(int u,int v,int w){
    node[u].firstEdge = new Node::Edge(&node[u],&node[v],w);
}

inline bool spfa(){
    for(int i = 1;i <= N;i++){
        node[i].dist = INT_MAX;
        node[i].inQueue = false;
    }
    std::queue<Node *> q;
    node[1].dist = 0;
    node[1].inQueue = true;
    q.push(&node[1]);
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->inQueue = false;
        for(Node::Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                if(!e->t->inQueue){
                    q.push(e->t);
                    e->t->inQueue = true;
                    e->t->count++;
                    if(e->t->count > N) return false;
                }
            }
        }
    }
    return true;
}

int main(){
    scanf("%d%d%d",&N,&M,&K);
    for(int u,v,w,i = 1;i <= M;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    for(int u,v,w,i = 1;i <= K;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(v,u,-w);
    }
    if(!spfa())
        printf("%d",-1);
    else{
        if(node[N].dist == INT_MAX)
            printf("%d",-2);
        else
            printf("%d",node[N].dist);
    }
    return 0;
}

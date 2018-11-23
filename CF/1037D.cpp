#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;

struct Node{
    struct Edge *firstEdge;
    int num;bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

std::queue<Node *> od,q;
int N;

void bfs(){
    od.pop();q.push(&node[1]);
    std::set<Node *> S;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        v->vis = true;
        for(Edge *e = v->firstEdge;e;e = e->next) if(!e->t->vis) S.insert(e->t);
        while(!S.empty()){
            if(S.count(od.front())){
                S.erase(od.front());
                q.push(od.front());
                od.pop();
            }
            else{
                puts("No");
                return;
            }
        }
    }
    puts("Yes");
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    FOR(i,1,N){
        int x;scanf("%d",&x);
        od.push(&node[x]);
    }
    if(od.front() != &node[1]) puts("No");
    else bfs();
    //system("pause");
    return 0;
}
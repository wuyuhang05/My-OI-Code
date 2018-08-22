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
#define U unsigned
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000 + 5;
const int MAXM = 5000 + 5;

int N,M,K,s,t;

struct Node{
    struct Edge *firstEdge;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
    int l,r;
    bool val;
}pool[MAXM],*frog = pool;

struct Data{
    int u,v,l,r;
}a[MAXM];

Edge *New(Node *s,Node *t,int l,int r){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->l = l;ret->r = r;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int l,int r){
    node[u].firstEdge = New(&node[u],&node[v],l,r);
}

std::map<int,int> S;
int origin[MAXM*2],num[MAXM*2],cnt;

bool bfs(int l,int r){
    if(l > K) return false;
    for(int i = 1;i <= N;i++)
        node[i].vis = false;
    for(int i = 1;i <= M;i++){
        Edge *e = &pool[i];
        e->val = (e->l <= l) && (e->r >= r);
    }
    std::queue<Node *> q;
    q.push(&node[s]);
    node[s].vis = true;
    while(!q.empty()){
        Node *v = q.front();
        q.pop();
        // if(v == &node[t]) return true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->val && !e->t->vis){
                e->t->vis = true;
                q.push(e->t);
            }
        }
    }
    // return node[t].vis;
    return node[t].vis;
}

int main(){
    scanf("%d%d%d%d%d",&N,&M,&K,&s,&t);
    for(int u,v,l,r,i = 1;i <= M;i++){
        scanf("%d%d%d%d",&u,&v,&l,&r);
        add(u,v,l,r);
        S.insert(std::make_pair(l-1,0));
        S.insert(std::make_pair(r,0));
    }
    S.insert(std::make_pair(0,0));
    S.insert(std::make_pair(K,0));
    int tN = 0;
    for(std::map<int,int>::iterator it = S.begin();it != S.end();it++){
        it->second = ++tN;
        origin[tN] = it->first;
    }
    int ans = 0;
    for(int i = 2;i <= tN;i++){
        if(bfs(origin[i-1]+1,origin[i]))
            ans += origin[i] - origin[i-1];
    }
    printf("%d\n",ans);
    return 0;
}

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

const int MAXN = 2000+5;
const int MAXM = 10000+5;

struct Node{
    struct Edge *firstEdge;
    int du,num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXM],*frog = pool;

Edge *New(Node *s,Node *t){
    t->du++;
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
}

int N,M;
int d[MAXN];
#define P std::pair<int,Node *>
#define MP std::make_pair
std::priority_queue<P,std::vector<P>,std::greater<P> > q;
std::vector<int> ans;

inline void topsort(){
    FOR(i,1,N) if(!node[i].du) q.push(MP(N-d[i],&node[i]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        ans.push_back(v->num);
        //DEBUG(v->num);DEBUG(v->firstEdge);
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--e->t->du) q.push(MP(N-d[e->t->num],e->t));
        }
    }
    ROF(i,N-1,0) printf("%d ",ans[i]);puts("");
}

int t[MAXN];

inline int calc(int x){
    int cnt = 0;
    while(!q.empty()) q.pop(); // q.clear();
    FOR(i,1,N) node[i].du = t[i];
    FOR(i,1,N) if(!node[i].du) q.push(MP(N-d[i],&node[i]));
    while(!q.empty()){
        Node *v = q.top().second;q.pop();
        if(v == &node[x]) continue;
        if(N-cnt > d[v->num]) return N - cnt;
        cnt++;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!--e->t->du) q.push(MP(N-d[e->t->num],e->t));
        }
    }
    return N - cnt;
}

int main(){
    read(N);read(M);
    FOR(i,1,N) read(d[i]),node[i].num = i;
    FOR(i,1,M){ 
        int u,v;read(u);read(v);
        add(v,u);
    }
    FOR(i,1,N) t[i] = node[i].du;
    topsort();
    FOR(i,1,N) printf("%d ",calc(i));puts("");
    return 0;
}

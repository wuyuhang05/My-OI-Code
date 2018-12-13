#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;

struct Node{
    struct Edge *first,*cur;
    int level;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next,*rev;
    int cap,flow;
}pool[MAXN*MAXN],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
    Edge *ret = ++frog;
    *ret = (Edge){s,t,s->first,NULL,cap,0};
    return ret;
}

inline void add(int u,int v,int cap){
    node[u].first = New(&node[u],&node[v],cap);
    node[v].first = New(&node[v],&node[u],cap);
    node[u].first->rev = node[v].first;
    node[v].first->rev = node[u].first;
}

int N,S,T;

bool bfs(Node *s,Node *t){
    FOR(i,0,N){
        node[i].cur = node[i].first;
        node[i].level = 0;
    }
    std::queue<Node *> q;
    q.push(s);s->level = 1;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->first;e;e = e->next){
            if(e->flow < e->cap && !e->t->level){
                e->t->level = v->level + 1;
                q.push(e->t);
                if(e->t == t) return true;
            }
        }
    }
    return false;
}

int dfs(Node *v,Node *t,int limit=INT_MAX){
    int flow;
    if(v == t) return limit;
    for(Edge *&e = v->first;e;e = e->next){
        if((flow = dfs(e->t,t,std::min(limit,e->cap - e->flow)))){
            e->flow += flow;
            e->rev->flow -= flow;
            return flow;
        }
    }
    return 0;
}

int dinic(){
    int ans = 0,flow;
    while(bfs(&node[S],&node[T])){
        while((flow = dfs(&node[S],&node[T]))){
            ans += flow;
        }
    }
    return ans;
}

int n,m;
std::string str;
struct Data{
    int money;
    std::vector<int> num;
}a[MAXN];
int mac[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        char ch=getchar();
        int pos = 0,t = 0;
        while(ch != ' '){
            // DEBUG(str[pos]);
            t = (t<<3) + (t<<1) + (ch ^ '0');
            ch = getchar();
        }
        a[i].money = t;pos++;
        while(ch != '\n'){
            t = 0;
            while(ch != '\n' && ch != ' '){
                t = (t << 3) + (t << 1) + (ch ^ '0');
                pos++;
            }
            pos++;
            a[i].num.push_back(t);
        }
    }
    FOR(i,1,m) scanf("%d",mac+i);
    FOR(i,1,n){
        printf("%d:",a[i].money);
        FOR(i,0,(int)a[i].num.size()-1){
            printf("%d ",a[i].num[i]);
        }
        puts("");
    }
    return 0;
}
/*
有一个工厂，接到了 n 个订单，为了完成这些订单，工厂需要采购一些机器，一共可采购 m 台机器。我们知道完成每个订单的收益，也知道购买某个机器的开销。一个订单需要对应地购买某些机器，一台机器可以同时完成多个订单。现在工厂决定选择性地接一些订单，使得工厂的利润最大化。
*/
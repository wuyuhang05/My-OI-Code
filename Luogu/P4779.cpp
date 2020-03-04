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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

namespace fastIO{
    #define BUF_SIZE 100000
    #define OUT_SIZE 100000
    #define ll long long
    bool IOerror=0;
    inline char nc(){
        static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;
        if (p1==pend){
            p1=buf; pend=buf+fread(buf,1,BUF_SIZE,stdin);
            if (pend==p1){IOerror=1;return -1;}
        }
        return *p1++;
    }
    inline bool blank(char ch){return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';}
    inline void read(int &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    inline void read(ll &x){
        bool sign=0; char ch=nc(); x=0;
        for (;blank(ch);ch=nc());
        if (IOerror)return;
        if (ch=='-')sign=1,ch=nc();
        for (;ch>='0'&&ch<='9';ch=nc())x=x*10+ch-'0';
        if (sign)x=-x;
    }
    #undef ll
    #undef OUT_SIZE
    #undef BUF_SIZE
};
using namespace fastIO;

const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

int N,M,S;

struct Node{
    struct Edge *firstEdge;
    LL dist;bool used;
}node[MAXN];

struct Edge{
    Node *s,*t;
    LL w;Edge *next;
}pool[MAXM*2],*frog = pool;

Edge *New(Node *s,Node *t,LL w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,LL w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    // node[v].firstEdge = New(&node[v],&node[u],w);
}

inline void dijkstra(){
    FOR(i,1,N){
        node[i].dist = LLONG_MAX;
        node[i].used = false;
    }
    node[S].dist = 0;
    std::priority_queue<std::pair<LL,Node *>,std::vector<std::pair<LL,Node *> >,std::greater<std::pair<LL,Node *> > > q;
    q.push(std::make_pair(0ll,&node[S]));
    while(!q.empty()){
        Node *v = q.top().second;
        q.pop();
        if(v->used) continue;
        v->used = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist > v->dist + e->w){
                e->t->dist = v->dist + e->w;
                q.push(std::make_pair(e->t->dist,e->t));
            }
        }
    }
}

int main(){
    read(N);read(M);read(S);
    FOR(i,1,M){
        int u,v,w;
        read(u);read(v);read(w);
        add(u,v,w);
    }
    dijkstra();
    FOR(i,1,N) printf("%lld ",node[i].dist);
    return 0;
}

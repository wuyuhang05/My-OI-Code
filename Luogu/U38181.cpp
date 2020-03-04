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
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
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

const int MAXN = 50000 + 5;
const int MAXM = 100000 + 5;

struct Node{
    struct Edge *firstEdge;
    LL dist[3][2];
    bool used[3][2],only;
}node[MAXN];

struct Edge{
    Node *s,*t;
    LL w;
    Edge *next;
}pool[MAXM*2],*frog = pool;

Edge *New(Node *s,Node *t,LL w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->w = w;ret->next = s->firstEdge;
    return ret; 
}

int N,M,K;
#define P std::pair<LL,Node *>
#define MP std::make_pair

inline void dijkstra(int s,int point,int turn){ // 0 = harry,1 = lowen
    FOR(i,1,N){
        node[i].dist[point][turn] = LLONG_MAX;
        node[i].used[point][turn] = false;
    }
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(0ll,&node[s]));
    node[s].dist[point][turn] = 0;
    while(!q.empty()){
        Node *v = q.top().second;
        q.pop();
        if(v->used[point][turn] || (v->only && turn == 1)) continue;
        v->used[point][turn] = true;
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist[point][turn] > v->dist[point][turn] + e->w){
                e->t->dist[point][turn] = v->dist[point][turn] + e->w;
                q.push(MP(e->t->dist[point][turn],e->t));
            }
        }
    }
}

inline void add(int u,int v,LL w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

inline LL getans(int t1,int t2,int x,int y){ // who goes to x ,who goes to y
    LL ret = LLONG_MAX;
    if(x == y){
        // if(x == 0){
            if(node[t1].dist[0][x] < LLONG_MAX && node[t2].dist[1][x] < LLONG_MAX)
                ret = std::min(ret,node[t1].dist[0][x] + node[t2].dist[1][x]);
            if(node[t2].dist[0][x] < LLONG_MAX && node[t1].dist[2][x] < LLONG_MAX)
                ret = std::min(ret,node[t2].dist[0][x] + node[t1].d Œ§ist[2][x]);
            return ret;
    }
    if(node[t1].dist[0][x] == LLONG_MAX || node[t2].dist[0][y] == LLONG_MAX) return -1;
    ret = std::max(node[t1].dist[0][x] ,node[t2].dist[0][y]);
    return ret;
}

int main(){
    read(N);read(M);read(K);
    FOR(i,1,K){
        int x;read(x);node[x].only = true;
    }
    FOR(i,1,M){
        int u,v;LL w;
        read(u);read(v);read(w);
        add(u,v,w);
    }
    int x,y;read(x);read(y);
    dijkstra(1,0,0);dijkstra(1,0,1);// 0 = harry,1 = lowen
    dijkstra(x,1,0);dijkstra(x,1,1);
    dijkstra(y,2,0);dijkstra(y,2,1);
    // DEBUG(node[x].dist[0][0]);
    LL ans = LLONG_MAX;
    FOR(i,0,1){
        FOR(j,0,1){
            LL t = getans(x,y,i,j);// DEBUG(t);
            ans = std::min(ans,(t == -1) ? LLONG_MAX : t);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*
10 13 3
3 4 10
1 2 1
2 3 2
3 4 3
4 5 4
5 6 5
6 7 10
7 8 5
8 9 10
9 10 3
10 1 2
1 9 6
3 8 10
4 6 3
6 8
*/
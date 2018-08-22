#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#define LL long long
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
/*
 inline void read(int &x){
 scanf("%d",&x);
 }
 
 inline void read(LL &x){
 scanf("%lld",&x);
 }*/
const int MAXN = 100000 + 5;
const int MAXM = 200000 + 5;

int N,M;

struct Data{
    int u,v,w;
}e[MAXM];

struct Node{
    struct Edge *firstEdge;
    int dist[2];
    bool used;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[MAXM*2],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret-> w = w;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

inline void dij(int turn,int s){
    for(int i = 1;i <= N;i++){
        node[i].used = false;
        node[i].dist[turn] = INT_MAX;
    }
    std::priority_queue<std::pair<int,Node *> ,std::vector<std::pair<int,Node *> > ,std::greater<std::pair<int,Node *> > > q;
    node[s].dist[turn] = 0;
    node[s].used = true;
    q.push(std::make_pair(0,&node[s]));
    while(!q.empty()){
        Node *v = q.top().second;
        q.pop();
        // DEBUG(v);
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->t->dist[turn] > v->dist[turn] + e->w){
                e->t->dist[turn] = v->dist[turn] + e->w;
                if(!e->t->used){
                    q.push(std::make_pair(e->t->dist[turn],e->t));
                    e->t->used = true;
                }
            }
        }
    }
}

int main(){
    read(N);read(M);
    for(int i = 1;i <= M;i++){
        read(e[i].u);read(e[i].v);read(e[i].w);
        add(e[i].u,e[i].v,e[i].w);
    }
    dij(0,1);
    dij(1,N);
    for(int i = 1;i <= N;i++){
        // DEBUG(node[i].dist[0]);DEBUG(node[i].dist[1]);
        printf("%d\n",node[i].dist[0] + node[i].dist[1]);
    }
    for(int i = 1;i <= M;i++){
        int ans = node[e[i].u].dist[0] + e[i].w + node[e[i].v].dist[1];
        // DEBUG(node[e[i].u].dist[0]);DEBUG(node[e[i].v].dist[1]);
        ans = std::min(ans,node[e[i].v].dist[0] + e[i].w + node[e[i].u].dist[1]);
        printf("%d\n",ans);
    }
    return 0;
}


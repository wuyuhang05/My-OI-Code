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

const int MAXN = 10000 + 5;
const int MAXM = 200000 + 5;

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

struct Node{
    struct Edge *firstEdge;
    int dist;
    bool can,cann;
    bool vis;
    //DEBUG
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
    bool opt;
}pool[MAXM<<2],*frog = pool;

Edge *New(Node *s,Node *t,bool opt){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->opt = opt;ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v],true);
    node[v].firstEdge = New(&node[v],&node[u],false);
}

int N,M,s,t;

void bfs1(){
    std::queue<Node *> q;
    q.push(&node[t]);
    node[t].cann = node[t].can = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(e->opt) continue;
            if(!e->t->can){
                e->t->cann = e->t->can = true;
                q.push(e->t);
            }
        }
    }
    FOR(i,1,N){
        if(!node[i].can){
            for(Edge *e = node[i].firstEdge;e;e = e->next){
                if(e->opt) continue;
                if(e->t->cann){
                    e->t->cann = false;
                }
            }
        }
    }
    FOR(i,1,N){
        node[i].can = node[i].can & node[i].cann;
    }
}

int bfs2(){
    if(!node[s].can) return -1;
    std::queue<Node *> q;
    q.push(&node[s]);
    node[s].vis = true;
    while(!q.empty()){
        Node *v = q.front();q.pop();
        for(Edge *e = v->firstEdge;e;e = e->next){
            if(!e->opt) continue;
            if(!e->t->can) continue;
            if(!e->t->vis){
                e->t->dist = v->dist + 1;
                e->t->vis = true;
                q.push(e->t);
            }
        }
    }
    return node[t].dist;
}

int main(){
    // FOR(i,1,1000) node[i].num = i;
    read(N);read(M);
    FOR(i,1,M){
        int x,y;read(x);read(y);
        if(x == y) continue;
        add(x,y);
    }
    // for(Edge *e = node[4].firstEdge;e;e = e->next){
    //     DEBUG(e->t->num);DEBUG(e->opt);
    // }
    read(s);read(t);
    bfs1();
    // FOR(i,1,N) DEBUG(node[i].can);
    int ans = bfs2();
    printf("%d\n",ans == 0 ? -1 : ans);
    return 0;
}
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

struct Node{
    struct Edge *firstEdge;
    bool p,vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    int w;
    Edge *next;
}pool[(MAXN<<1)+1],*frog = pool;

Edge *New(Node *s,Node *t,int w){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;ret->w = w;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v,int w){
    node[u].firstEdge = New(&node[u],&node[v],w);
    node[v].firstEdge = New(&node[v],&node[u],w);
}

int N,K;
LL ans;

int dfs(Node *v){
    v->vis = true;
    LL t=0,ret=0,max=0;
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t->vis) continue;
        t = std::min(dfs(e->t),e->w);
        ret += t;max = std::max(max,t);
    }
    ans += ret;
    if(v->p) return INT_MAX;
    ans -= max;
    return max;
}

int main(){
    read(N);read(K);
    FOR(i,1,K){
        int x;read(x);
        node[x].p = true;
    }
    FOR(i,1,N-1){
        int x,y,z;read(x);read(y);read(z);
        add(x,y,z);
    }
    dfs(&node[0]);
    printf("%lld\n",ans);
    return 0;
}
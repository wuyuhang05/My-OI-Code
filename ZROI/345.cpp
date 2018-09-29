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
#define FOR(i,a,b) for(Re int i = (a);i <= (b);++i)
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define EFOR(e,v) for(Re Edge *e = v->firstEdge;e;e = e->next)
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

const int MAXN = 1000000 + 5;

int N,p,q;
char str[MAXN];

struct Node{
    Node *opt;
    struct Edge *firstEdge;
    bool vis;
    int pos;LL ans;
    std::priority_queue<LL,std::vector<LL>,std::greater<LL> > q;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
    // Edge(Node *s,Node *t) : s(s),t(t),next(s->firstEdge) {}
}pool[MAXN*2],*frog = pool;

Edge *New(int s,int t){
    Edge *ret = ++frog;
    ret->s = &node[s];ret->t = &node[t];
    ret->next = node[s].firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(u,v);
    // node[v].firstEdge = New(v,u);
}

inline LL calc(Node *v){
    LL cost = (str[v->pos] == '+') ? p : q;
    while(v->q.size() > 1){
        v->q.pop();LL t = v->q.top();
        v->q.pop();v->q.push(t+cost);
    }
    return v->q.top();
}

void dfs(Node *v,Node *fa,Node *opt){
    // v->vis = true;
    v->opt = opt;
    if(!v->firstEdge){
        fa->opt->q.push(0);
        return;
    }
    EFOR(e,v){
        // if(e->t->vis) continue;
        if(e->t->pos < N && str[v->pos] != str[e->t->pos])
            dfs(e->t,v,e->t);
        else dfs(e->t,v,opt);
    }
    if(v == opt) fa->opt->q.push(v->ans = calc(v));
}

bool pdr[MAXN]; // pd root
int root;

int main(){
    read(N);read(p);read(q);
    FOR(i,1,N-1){
        str[i] = nc();
    }
    FOR(i,1,(N<<1) - 2){
        int u,v;read(u);read(v);
        add(u,v);pdr[v] = true;
        node[i].pos = i;
    }
    node[(N << 1) - 1].pos = (N << 1) - 1;
    while(pdr[++root]);
    node[0].opt = &node[0];
    dfs(&node[root],&node[0],&node[root]);
    printf("%lld\n",node[root].ans);
    return 0;
}
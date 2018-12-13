#pragma comment(linker, "/STACK:102400000,102400000")
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

const int MAXN = 100000+5;
const int MAXM = 300000+5;

struct Node{
    struct Edge *firstEdge;
    Node *fa;
    int col;
    bool vis;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXM<<1],*frog = pool;

Edge *New(Node *s,Node *t){
    Edge *ret = ++frog;
    ret->s = s;ret->t = t;
    ret->next = s->firstEdge;
    return ret;
}

inline void add(int u,int v){
    node[u].firstEdge = New(&node[u],&node[v]);
    node[v].firstEdge = New(&node[v],&node[u]);
}

int N,M,ts;
bool odd,even;

inline void prework(){
    CLR(pool,0);frog = pool;
    FOR(i,1,N) node[i].firstEdge = NULL,node[i].col = 0,node[i].fa = NULL,node[i].vis = false;
    even = odd = false;
}

bool calc(Node *x,Node *y){
    while(x != y){
        if(!x) return false;
        if(x->vis) return true;
        x->vis = true;
        x = x->fa;
    }
    return false;
}

void dfs(Node *v){
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(e->t == v->fa) continue;
        if(!e->t->col){
            e->t->col = 3-v->col;
            e->t->fa = v;
            dfs(e->t);
        }
        else{
            if(e->t->col == v->col){
                odd = true;
                if(calc(v,e->t)) even = true;
            }
            else even = true;
        }
    }
}

inline void Solve(){
    read(N);read(M);
    prework();
    FOR(i,1,M){
        int u,v;read(u);read(v);
        add(u,v);
    }
    FOR(i,1,N) if(!node[i].col) node[i].col = 1,dfs(&node[i]);
    puts(odd ? "YES" : "NO");
    puts(even ? "YES" : "NO");
}

int main(){
    int T;read(T);
    while(T--) Solve();
    system("pause");
    return 0;
}
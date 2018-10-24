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
#define int long long
const int ha = 998244353;

inline LL qpow(LL a,LL n=ha-2){
    LL ret = 1ll;
    while(n){
        if(n & 1) ret = (ret * a) % ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret%ha;
}

const int MAXN = 200000 + 5;

struct Node{
    struct Edge *firstEdge;
    int depth,num;
}node[MAXN];

struct Edge{
    Node *s,*t;
    Edge *next;
}pool[MAXN<<1],*frog = pool;

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

const int MAXF = MAXN*2;
int N,M,log2N;
int f[MAXN][40];
int fac[MAXF+20];

inline void calc(int x,int y,int p){
    if(node[x].depth < node[y].depth) std::swap(x,y);
    int d = node[x].depth - node[y].depth;
    int dx = node[x].depth-node[p].depth,dy=node[y].depth-node[p].depth;
    LL res = 0ll;
    res = 1ll*fac[d+2*dy]*qpow(fac[dy])%ha*qpow(fac[d+dy])%ha;
    printf("%lld\n",1ll*res*qpow(qpow(2,dx+dy))%ha);
}

void dfs(Node *v){
    FOR(i,1,log2N){
        if(v->depth <= (1 << i)) break;
        f[v->num][i] = f[f[v->num][i-1]][i-1];
    }
    for(Edge *e = v->firstEdge;e;e = e->next){
        if(!e->t->depth){
            e->t->depth = v->depth + 1;
            f[e->t->num][0] = v->num;
            dfs(e->t);
        }
    }
}

inline void pre(){
    FOR(i,1,N){
        node[i].num = i;
        node[i].depth = 0;
    }
    log2N = log(N)/log(2) + 1;
    node[1].depth = 1;
    dfs(&node[1]);
    fac[0] = fac[1] = 1;
    FOR(i,2,MAXF) fac[i] = (fac[i-1]*i)%ha;
}

inline int lca(int x,int y){
    int dx = node[x].depth,dy = node[y].depth;
    if(dx != dy){
        if(dx < dy){
            std::swap(x,y);
            std::swap(dx,dy);
        }
        int d = dx-dy;
        FOR(i,0,log2N){
            if((1 << i) & d) x = f[x][i];
        }
    }
    if(x == y) return x;
    ROF(i,log2N,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

signed main(){
    read(N);
    FOR(i,1,N-1){
        int u,v;read(u);read(v);
        add(u,v);
    }
    pre();
    int M;read(M);
    while(M--){
        int x,y;read(x);read(y);
        int l = lca(x,y);
        //LL ans = calc(x,y,l);
        //printf("%lld\n",ans);
        calc(x,y,l);
    }
    return 0;
}
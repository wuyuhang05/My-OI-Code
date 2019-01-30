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

#define fi first
#define lc (ch[x][0])
#define se second
#define U unsigned
#define rc (ch[x][1])
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;

int ch[MAXN][2],f[MAXN],val[MAXN],sum[MAXN],tag[MAXN],son[MAXN];

inline bool nroot(int x){
    return ch[f[x]][0] == x || ch[f[x]][1] == x;
}

inline void reverse(int x){
    std::swap(lc,rc);tag[x] ^= 1;
}

inline void pushdown(int x){
    if(tag[x]){
        if(lc) reverse(lc);
        if(rc) reverse(rc);
        tag[x] = 0;
    }
}

inline void pushup(int x){
    sum[x] = sum[lc]^sum[rc]^val[x]^son[x];
}

inline void rotate(int x){
    int y = f[x],z = f[y],k = ch[y][1]==x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;
    ch[x][!k] = y;ch[y][k] = w;
    if(w) f[w] = y;
    f[y] = x;f[x] = z;
    pushup(y);
}

int st[MAXN];

inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x],z = f[y];
        if(nroot(y)) rotate((ch[y][0] == x)^(ch[z][0]==y) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = f[y = x]){
        splay(x);son[x] ^= sum[rc]^sum[y];
        rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline void link(int x,int y){
    makeroot(x);makeroot(y);f[x] = y;
    son[y] ^= sum[x];pushup(y);
}

inline void split(int x,int y){
    makeroot(x);access(y);splay(y);
}

inline void cut(int x,int y){
    split(x,y);f[x] = ch[y][0] = 0;
}

int N,M;
struct Edge{
    int u,v,w;
}e[MAXN<<2];
int cnt,S;

int main(){
    srand(20050117);
    scanf("%*d%d%d",&N,&M);
    FOR(i,1,N-1){
        int x,y;scanf("%d%d",&x,&y);
        link(x,y);
    }
    while(M--){
        int x,y,u,v,opt;scanf("%d%d",&opt,&x);
        if(opt == 1){
            scanf("%d%d%d",&y,&u,&v);
            cut(x,y);link(u,v);
        }
        if(opt == 2){
            scanf("%d",&y);
            e[++cnt] = (Edge){x,y,rand()};
            makeroot(x);val[x] ^= e[cnt].w;pushup(x);
            makeroot(y);val[y] ^= e[cnt].w;pushup(y);
            S ^= e[cnt].w;
        }
        if(opt == 3){
            makeroot(e[x].u);val[e[x].u] ^= e[x].w;pushup(e[x].u);
            makeroot(e[x].v);val[e[x].v] ^= e[x].w;pushup(e[x].v);
            S ^= e[x].w;
        }
        if(opt == 4){
            scanf("%d",&y);split(x,y);
            puts(sum[x]^S ? "NO" : "YES");
        }
    }
    return 0;
}
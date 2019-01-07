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
#define lc c[x][0]
#define rc c[x][1]
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300000+5;

struct Edge{
    int u,v,a,b;
    bool operator < (const Edge &other) const {
        return a < other.a;
    }
}e[MAXN<<1];

int c[MAXN][2],val[MAXN],tag[MAXN],f[MAXN];
int max[MAXN],pos[MAXN];

inline bool nroot(int x){
    return c[f[x]][0] == x || c[f[x]][1] == x;
}

inline void pushup(int x){
    if(val[x] > max[lc] && val[x] > max[rc]){
        max[x] = val[x];pos[x] = x;
    }
    else{
        max[x] = std::max(max[lc],max[rc]);
        pos[x] = max[lc] > max[rc] ? pos[lc] : pos[rc];
    }
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

inline void rotate(int x){
    int y = f[x],z = f[y];
    int k = c[y][1] == x,w = c[x][!k];
    if(nroot(y)) c[z][c[z][1]==y] = x;
    c[x][!k] = y;c[y][k] = w;
    f[w] = y;
    f[y] = x;f[x] = z;
    pushup(y);
}

int st[MAXN];
inline void splay(int x){
    int y = x,z;st[z=1]=y;
    while(nroot(y)) st[++z] = y = f[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = f[x];z = f[y];
        if(nroot(y)) rotate((c[y][0]==x)^(c[z][0]==y) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y=0;x;x = f[y = x]){
        splay(x);rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline void split(int x,int y){
    makeroot(x);access(y);splay(y);
}

inline int findroot(int x){
    access(x);splay(x);
    while(lc) pushdown(x),x=lc;
    return x;
}

inline void link(int x,int y){
    makeroot(x);f[x] = y;
}

inline void cut(int x,int y){
    makeroot(x);
    if(findroot(y) == x && f[x] == y && !rc){
        f[x] = c[y][0] = 0;pushup(y);
    }
}

inline bool connected(int x,int y){
    int fx = findroot(x),fy = findroot(y);
    return fx == fy;
}

inline void calc(int x,int y,int &mx,int &id){
    split(x,y);mx = max[y];id = pos[y];
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,M) scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].a,&e[i].b);
    int ans = INT_MAX;
    std::sort(e+1,e+M+1);
    FOR(i,1,N+M){
        max[i] = val[i] = 0;pos[i] = i;
        if(i > N) max[i] = val[i] = e[i-N].b;
    }
    FOR(i,1,M){
        int mx,id,x = e[i].u,y = e[i].v;
        if(connected(x,y)){
            calc(x,y,mx,id);
            if(mx > e[i].b){
                cut(id,e[id-N].u);cut(id,e[id-N].v);
                link(N+i,x);link(N+i,y);
            }
        }else{
            link(N+i,x);link(N+i,y);
        }
        if(connected(1,N)){
            calc(1,N,mx,id);
            ans = std::min(ans,mx+e[i].a);
        }
        if(e[i].a > ans) break;
    }
    printf("%d\n",ans==INT_MAX ? -1 : ans);
    return 0;
}
/*
4 5
1 2 19 1
2 3 8 12
2 4 12 15
1 3 17 8
3 4 1 17
*/
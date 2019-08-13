/*
 * Author: RainAir
 * Time: 2019-08-06 20:12:56
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;

#define lc (ch[x][0])
#define rc (ch[x][1])
int fa[MAXN],ch[MAXN][2],sm[MAXN],val[MAXN],tag[MAXN];

inline bool nroot(int x){
    return ch[fa[x]][0] == x || ch[fa[x]][1] == x;
}

inline void pushup(int x){
    sm[x] = sm[lc]+sm[rc]+val[x];
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
    int y = fa[x],z = fa[y],k = ch[y][1] == x,w = ch[x][!k];
    if(nroot(y)) ch[z][ch[z][1]==y] = x;
    ch[x][!k] = y;ch[y][k] = w;
    if(w) fa[w] = y;fa[y] = x;fa[x] = z;
    pushup(y);
}

int st[MAXN],dep[MAXN];

inline void splay(int x){
    int y = x,z;st[z = 1] = y;
    while(nroot(y)) st[++z] = y = fa[y];
    while(z) pushdown(st[z--]);
    while(nroot(x)){
        y = fa[x];z = fa[y];
        if(nroot(y)) rotate((ch[z][0] == y)^(ch[y][0] == x) ? x : y);
        rotate(x);
    }
    pushup(x);
}

inline void access(int x){
    for(int y = 0;x;x = fa[y = x]){
        splay(x);rc = y;pushup(x);
    }
}

inline void makeroot(int x){
    access(x);splay(x);reverse(x);
}

inline int findroot(int x){
    access(x);splay(x);
    while(lc) pushdown(x),x = lc;
    splay(x);return x;
}

inline void split(int x,int y){
    makeroot(x);
    access(y);splay(y);
}

inline void link(int x,int y,int w){
    //makeroot(x);
    if(dep[x] > dep[y]) std::swap(x,y);
    int u = findroot(x),v = findroot(y);
    val[u] = val[u]+val[v]-w;
    splay(y);fa[y] = x;
}

inline int cut(int x,int y){
    if(dep[x] > dep[y]) std::swap(x,y);
    int u = findroot(x);
    int t = val[u];//val[y] = val[u];
    access(y);splay(x);fa[y] = ch[x][1] = 0;
    val[y] = t;pushup(y);
    return t;
}

struct Edge{
    int u,v,w;
}e[MAXN];
int n,m,q;
bool zt[MAXN];
std::vector<int> G[MAXN];

inline void dfs(int v,int fa=0){
    for(auto x:G[v]){
        if(x == fa) continue;
        dep[x] = dep[v] + 1;dfs(x,v);
    }
}

int main(){
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n-1) scanf("%d%d",&e[i].u,&e[i].v),G[e[i].u].pb(e[i].v),G[e[i].v].pb(e[i].u);
    std::fill(val+1,val+n+1,1);dep[1] = 1;dfs(1);
    FOR(i,1,m){
        int x;scanf("%d",&x);
        if(zt[x]){
            e[x].w = cut(e[x].u,e[x].v);
        }
        else{
            link(e[x].u,e[x].v,e[x].w);
        }
        zt[x] ^= 1;
    }
    FOR(i,1,q){
        int x;scanf("%d",&x);
        printf("%d\n",val[findroot(x)]);
    }
    return 0;
}

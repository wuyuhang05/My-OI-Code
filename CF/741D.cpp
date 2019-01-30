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

const int MAXN = 500000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],dep[MAXN],size[MAXN],fa[MAXN],son[MAXN],val[MAXN],_;

inline void add(int u,int v,int w){
    e[++_] = (Edge){v,head[u]};head[u] = _;
}

void dfs1(int v){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v]) continue;
        val[e[i].to] = val[v]^(1<<e[i].w);dep[e[i].to] = dep[v];
        fa[e[i].to] = fa[v];dfs1(e[i].to);
        son[v] = size[son[v]] < size[e[i].to] ? e[i].to : son[v];
    }
}

int max,f[1<<26],ans[MAXN],lcadep;

inline void calc(int lca,int v){
    int now = val[v];
    max = std::max(max,f[now]+dep[v]-2*dep[lca]);
    q
}

void dfs2()

int main(){
    return 0;
}
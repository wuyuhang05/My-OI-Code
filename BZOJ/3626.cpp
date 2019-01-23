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

#define lc (x<<1)
#define rc (x<<1|1)
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

const int MAXN = 50000+5;

struct Edge{
    int to,next;
}e[MAXN<<1];

int head[MAXN],dfn[MAXN],size[MAXN],son[MAXN],fa[MAXN],cnt;
int sum[MAXN<<2],tag[MAXN<<2];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
} 

void dfs1(int v){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v]) continue;
        fa[e[i].to] = v;
    }
}

int main(){
    return 0;
}
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
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
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

struct Edge{
    int to,next;
}e[MAXN<<1];
int head[MAXN],cnt,len[MAXN],son[MAXN],N;
LL t[MAXN<<2],*f[MAXN],*g[MAXN],*id = t,ans;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

inline void dfs(int v,int fa){
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        son[v] = len[e[i].to] > len[son[v]] ? e[i].to : son[v];
    }
    len[v] = len[son[v]]+1;
}

void dp(int v,int fa){
    if(son[v]){
        f[son[v]] = f[v] + 1;g[son[v]] = g[v] - 1;
        dp(son[v],v);
    }
    f[v][0] = 1;ans += g[v][0];
    for(int i = head[v];i;i = e[i].next){
        int to = e[i].to;if(to == fa || to == son[v]) continue;
        f[to] = id;id += len[to]<<1;g[to] = id;id += len[to] << 1;dp(to,v);
        FOR(j,0,len[to]-1){
            if(j) ans += f[v][j-1]*g[to][j];
            ans += f[to][j]*g[v][j+1];
        }
        FOR(j,0,len[to]-1){
            g[v][j+1] += f[v][j+1]*f[to][j];
            if(j) g[v][j-1] += g[to][j];
            f[v][j+1] += f[to][j];
        }
    }
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1,0);f[1] = id;id += len[1]<<1;g[1] = id;id += len[1]<<1;
    dp(1,0);
    printf("%d\n",ans);
    return 0;
}
/*
f[i][j]
*/
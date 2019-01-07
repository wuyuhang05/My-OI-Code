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

const int MAXN = 300000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],cnt;
int N,M,K;
int f[MAXN][23],fa[MAXN],depth[MAXN],in[MAXN],out[MAXN],ts;
float log2N;
inline void add(int u,int v,int w){
    //printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

void dfs(int v,int fa){
    in[v] = ++ts;
    printf("%d\n",v);
    FOR(i,1,log2N){
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head[v];i;i = e[i].next){
        //if(e[i].to != fa){
        if(e[i].to != fa){
            depth[e[i].to] = depth[v] + 1;
            f[e[i].to][0] = v;
            dfs(e[i].to,v);
        }
    }
    out[v] = ts;
}

inline int query(int a,int b){
    int da = depth[a],db = depth[b];
    if(da != db){
        if(da < db) std::swap(a,b),std::swap(da,db);
        int d = da-db;
        FOR(i,0,log2N){
            if((1<<i)&d) a = f[a][i];
        }
    }
    if(a == b) return a;
    ROF(i,log2N,0){
        if(f[a][i] == f[b][i]) continue;
        a = f[a][i],b = f[b][i];
    }
    return f[a][0];
}

int main(){
    freopen("1.in","r",stdin);
    freopen("ss.out","w",stdout);
    scanf("%d%d%d",&N,&M,&K);
    FOR(i,1,N-1){
        int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    log2N = log2(N);
    depth[1] = 1;dfs(1,0);
    return 0;
}
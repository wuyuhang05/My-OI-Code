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
#define int LL
const int MAXN = 300000+5;

struct Edge{
    int to;LL w;int next;
}e[MAXN<<1];
int head[MAXN],cnt;
int fa[MAXN],f[MAXN][50];
LL max[MAXN][50],min[MAXN][50],dep[MAXN];

struct Data{
    int u,v;LL w;
    bool in;
    bool operator < (const Data &other) const {
        return w < other.w;
    }
}d[MAXN<<1];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int N,M,mst;

inline void Kruskal(){
    FOR(i,1,N) fa[i] = i;
    std::sort(d+1,d+M+1);
    int cnt = 0;
    FOR(i,1,M){
        int fx = find(d[i].u),fy = find(d[i].v);
        if(fx == fy) continue;
        add(d[i].u,d[i].v,d[i].w);
        add(d[i].v,d[i].u,d[i].w);
        d[i].in = true;
        fa[fy] = fx;mst += d[i].w;
        if(++cnt == N-1) break;
    }
}

float log2N;

void dfs(int v,int fa=0){
    FOR(i,1,log2N){
        if(dep[v] <= (1<<i)) break;
        f[v][i] = f[f[v][i-1]][i-1];
        max[v][i] = std::max(max[v][i],max[f[v][i-1]][i-1]);
        min[v][i] = std::max(min[v][i],min[f[v][i-1]][i-1]);
        if(max[v][i-1] > max[f[v][i-1]][i-1])
            min[v][i] = std::max(min[v][i],max[f[v][i-1]][i-1]);
        else if(max[v][i-1] < max[f[v][i-1]][i-1])
            min[v][i] = std::max(min[v][i],max[v][i-1]);
        //DEBUG(min[v][i]);DEBUG(min[f[v][i-1]][i-1]);
    }
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v]+1;
        max[e[i].to][0] = e[i].w;
        min[e[i].to][0] = LLONG_MIN;
        f[e[i].to][0] = v;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    int dx = dep[x],dy = dep[y];
    if(dx != dy){
        if(dx < dy) std::swap(dx,dy),std::swap(x,y);
        int d = dx-dy;
        FOR(i,0,log2N) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,log2N,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i];y = f[y][i];
    }
    return f[x][0];
}

inline int calc(int x,int y,int lim){
    LL ans = LLONG_MIN;
    ROF(i,log2N,0){
        if(dep[f[x][i]] >= dep[y]){
            //DEBUG(lim);DEBUG(max[x][i]);
            if(lim != max[x][i]) ans = std::max(ans,max[x][i]);
            else ans = std::max(ans,min[x][i]);
            x = f[x][i];
        }
    }
    //DEBUG(ans);
    return ans == LLONG_MIN ? 0 : ans;
}

signed main(){CLR(f,-1);
    scanf("%lld%lld",&N,&M);
    FOR(i,1,M) scanf("%lld%lld%lld",&d[i].u,&d[i].v,&d[i].w);
    Kruskal();log2N = log2(N);min[1][0] = LLONG_MIN;dep[1] = 1;
    dfs(1);
    LL ans = LLONG_MAX;
    FOR(i,1,M){
        if(d[i].in) continue;
        int l = lca(d[i].u,d[i].v);
        // DEBUG(d[i].u);DEBUG(d[i].v);DEBUG(l);
        // DEBUG(calc(d[i].u,l,d[i].w));DEBUG(calc(d[i].v,l,d[i].w));
        // DEBUG(mst-std::max(calc(d[i].u,l,e[i].w),calc(d[i].v,l,e[i].w))+e[i].w);
        ans = std::min(ans,mst-std::max(calc(d[i].u,l,d[i].w),calc(d[i].v,l,d[i].w))+d[i].w);
    }
    printf("%lld\n",ans);
    return 0;
}
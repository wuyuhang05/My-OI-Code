/*
 * Author: RainAir
 * Time: 2019-10-03 15:09:12
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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;
const int MAXM = 20;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int f[MAXN][MAXM+1],head[MAXN],dep[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

inline void dfs(int v,int fa=0){
    f[v][0] = fa;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,MAXM) if(d&(1<<i)) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

int ans[MAXN],w[MAXN],U[MAXN*4];
std::vector<int> B[MAXN],E[MAXN];

inline void dfs1(int v,int fa=0){
    int t = U[w[v]+dep[v]];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs1(e[i].to,v);
    }
    for(auto x:B[v]) U[x]++;
    ans[v] += std::max(0,U[w[v]+dep[v]]-t);
    for(auto x:E[v]) U[x]--;
    B[v].clear();E[v].clear();
}

inline void dfs2(int v,int fa=0){
    int t = U[dep[v]-w[v]+MAXN];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs2(e[i].to,v);
    }
    for(auto x:B[v]) U[x]++;
    ans[v] += std::max(0,U[dep[v]-w[v]+MAXN]-t);
    for(auto x:E[v]) U[x]--;
}

int n,m;
int s[MAXN],t[MAXN],l[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    FOR(i,1,n) scanf("%d",w+i);dep[1] = 1;dfs(1);
    FOR(i,1,m) scanf("%d%d",s+i,t+i),l[i] = lca(s[i],t[i]);
    CLR(U,0);
    FOR(i,1,m){
        B[s[i]].pb(dep[s[i]]);
        E[l[i]].pb(dep[s[i]]);
    }
    dfs1(1);
    CLR(U,0);
    FOR(i,1,m){
        int len = dep[s[i]]+dep[t[i]]-2*dep[l[i]]-MAXN;
        B[t[i]].pb(dep[t[i]]-len);
        E[l[i]].pb(dep[t[i]]-len);
    }
    dfs2(1);
    FOR(i,1,m) if(dep[s[i]] - dep[l[i]] == w[l[i]]) ans[l[i]]--;
    FOR(i,1,n) printf("%d ",ans[i]);puts("");
    return 0;
}

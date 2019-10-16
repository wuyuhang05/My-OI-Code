/*
 * Author: RainAir
 * Time: 2019-10-07 12:28:08
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 4e5 + 5;
const int MAXM = 4e5 + 5;

int n,m,q,k,s;
std::vector<P> G[MAXN];
std::vector<int> T[MAXN];
struct Edge{
    int u,v,l,a;
    bool operator < (const Edge &t) const {
        return a > t.a;
    }
}e[MAXM];
int dis[MAXN];
bool used[MAXN];

inline void Dijkstra(){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,n) dis[i] = 1e9,used[i] = false;
    q.push(MP(dis[1] = 0,1));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = true;
        for(auto x:G[v]){
            if(dis[x.fi] > dis[v] + x.se){
                dis[x.fi] = dis[v] + x.se;
                q.push(MP(dis[x.fi],x.fi));
            }
        }
    }
}

int f[MAXN],tot = n;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void Union(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    T[fx].pb(++tot);T[fy].pb(tot);
    T[tot].pb(fx);T[tot].pb(fy);
    f[fx] = f[fy] = tot;
}

int val[MAXN];

inline void Kruskal(){
    std::sort(e+1,e+m+1);int cnt = 0;
    FOR(i,1,2*n) f[i] = i;
    FOR(i,1,m){
        int u = e[i].u,v = e[i].v,w = e[i].a;
        int fu = find(u),fv = find(v);
        if(fu == fv) continue;
        Union(fu,fv);val[tot] = w;
        if(++cnt == n-1) break;
    }
}

const int MAXL = 19;
int ff[MAXN][MAXL+1],dep[MAXN],mn[MAXN],la = 0;

inline void dfs(int v,int fa=0){
    FOR(i,1,MAXL) ff[v][i] = ff[ff[v][i-1]][i-1];
    if(v <= n) mn[v] = dis[v];
    else mn[v] = 1e9;
    for(auto x:T[v]){
        if(x == fa) continue;
        ff[x][0] = v;dep[x] = dep[v] + 1;
        dfs(x,v);mn[v] = std::min(mn[v],mn[x]);
    }
}

inline int query(int v,int p){
    ROF(i,MAXL,0){
        if(dep[v] > (1<<i) && val[ff[v][i]] > p) v = ff[v][i];
    }
    return mn[v];
}

inline void clear(){
    la = 0;
    FOR(i,1,n) G[i].clear();
    FOR(i,1,tot) T[i].clear(),dep[i] = val[i] = 0;
}

inline void Solve(){
    scanf("%d%d",&n,&m);tot = n;
    FOR(i,1,m) scanf("%d%d%d%d",&e[i].u,&e[i].v,&e[i].l,&e[i].a);
    scanf("%d%d%d",&q,&k,&s);
    FOR(i,1,m) G[e[i].u].pb(MP(e[i].v,e[i].l)),G[e[i].v].pb(MP(e[i].u,e[i].l));
    Dijkstra();Kruskal();dep[tot] = 1;dfs(tot);
    FOR(i,1,q){
        int v,p;scanf("%d%d",&v,&p);
        v = (v+k*la-1)%n+1;
        p = (p+k*la)%(s+1);
        printf("%d\n",la = query(v,p));
    }
    clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

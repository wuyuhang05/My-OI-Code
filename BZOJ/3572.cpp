/*
 * Author: RainAir
 * Time: 2019-10-30 14:51:37
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;
const int MAXM = 19;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dfn[MAXN],dep[MAXN],sz[MAXN],f[MAXN][MAXM+1];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = ++ts;sz[v] = 1;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        f[e[i].to][0] = v;
        dfs(e[i].to,v);sz[v] += sz[e[i].to];
    }
}

inline int lca(int x,int y){
    if(!x || !y) return 0;
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,MAXM){
            if((1<<i)&d) x = f[x][i];
        }
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

inline int calc(int x,int y){
    return dep[x] + dep[y] - 2*dep[lca(x,y)];
}

inline bool cmp(int x,int y){
    return dfn[x] < dfn[y];
}

std::vector<int> node,nd,G[MAXN],del;
int n,bel[MAXN],stk[MAXN],ans[MAXN],ext[MAXN],tp; // shortest
// ans: 绝对控制 ,ext: 相对控制

inline void up(int v){
    ext[v] = sz[v];
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        up(x);
        if(!bel[x]) continue;
        int t1 = calc(bel[x],v),t2 = calc(bel[v],v);
        if(!bel[v] || t1 < t2 || (t1 == t2 && bel[x] < bel[v]))
            bel[v] = bel[x];
    }
}

inline void down(int v){
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        int t1 = calc(bel[v],x),t2 = calc(bel[x],x);
        if(!bel[x] || t1 < t2 || (t1 == t2 && bel[v] < bel[x]))
            bel[x] = bel[v];
        down(x);
    }
}

inline void update(int a,int b){
    int x = b;
    ROF(i,MAXM,0){
        if(dep[f[x][i]] > dep[a]) x = f[x][i];
    }
    ext[a] -= sz[x];
    if(bel[a] == bel[b]){
        ans[bel[a]] += sz[x]-sz[b];
        return;
    }
    int mid = b;
    ROF(i,MAXM,0){
        int t = f[mid][i];
        if(dep[t] <= dep[a]) continue;
        int t1 = calc(bel[b],t),t2 = calc(bel[a],t);
        if(t1 < t2 || (t1 == t2 && bel[b] < bel[a])) mid = t;
    }
    ans[bel[a]] += sz[x]-sz[mid];
    ans[bel[b]] += sz[mid]-sz[b];
}

inline void Solve(){
    nd = node;del.clear();
    FOR(i,0,(int)node.size()-1) bel[node[i]] = node[i];
    if(!bel[1]) node.pb(1);
    std::sort(all(node),cmp);
    stk[tp = 1] = 0;del.pb(0);
    FOR(i,0,(int)node.size()-1){
        int u = node[i],l = lca(u,stk[tp]);
        del.pb(u);
        if(l == stk[tp]){
            stk[++tp] = u;
            continue;
        }
        while(tp >= 2 && dep[stk[tp-1]] >= dep[l]){
            G[stk[tp-1]].pb(stk[tp]);
            tp--;
        }
        if(stk[tp] != l){
            del.pb(l);
            G[l].pb(stk[tp]);
            stk[tp] = l;
        }
        stk[++tp] = u;
    }
    FOR(i,2,tp) G[stk[i-1]].pb(stk[i]);
    up(G[0][0]);down(G[0][0]);
    FOR(i,0,(int)del.size()-1){
        int v = del[i];
        if(!v) continue;
        FOR(i,0,(int)G[v].size()-1){
            int x = G[v][i];
            update(v,x);
        }
    }
    FOR(i,0,(int)del.size()-1) ans[bel[del[i]]] += ext[del[i]];
    FOR(i,0,(int)nd.size()-1) printf("%d ",ans[nd[i]]);puts("");
    FOR(i,0,(int)del.size()-1) G[del[i]].clear(),ans[del[i]] = ext[del[i]] = bel[del[i]] = 0;
}

int main(){
    freopen("a.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dep[1] = 1;dfs(1);int q;scanf("%d",&q);
    while(q--){
        node.clear();
        int k;scanf("%d",&k);
        FOR(i,1,k){
            int x;scanf("%d",&x);
            node.pb(x);
        }
        Solve();
    }
    return 0;
}

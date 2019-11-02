/*
 * Author: RainAir
 * Time: 2019-10-29 15:29:21
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
#define int LL
const int MAXN = 3e5 + 5;
const int MAXM = 19;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int n,m;
int dfn[MAXN];
int f[MAXN][MAXM+1],mn[MAXN],dep[MAXN];

inline bool cmp(int a,int b){
    return dfn[a] < dfn[b];
}

inline void dfs1(int v,int fa=0){
    static int ts = 0;
    dfn[v] = ++ts;
    FOR(i,1,MAXM){
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        f[e[i].to][0] = v;dep[e[i].to] = dep[v] + 1;
        mn[e[i].to] = std::min(mn[v],e[i].w);
        dfs1(e[i].to,v);
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

int stk[MAXN],tp;
std::vector<int> G[MAXN],node,del;
int F[MAXN];
bool key[MAXN];

inline void dfs2(int v,int fa){
    F[v] = mn[v];
    int sm = 0;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(x == fa) continue;
        dfs2(x,v);
        sm += F[x];
    }
    if(!key[v]) F[v] = std::min(F[v],sm);
}

inline void Solve(){
//    DEBUG(lca(6,10));
    FOR(i,0,(int)node.size()-1) key[node[i]] = 1;
    node.pb(1);
    std::sort(all(node),cmp);del.clear();
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
            G[stk[tp]].pb(stk[tp-1]);
            tp--;
        }
        if(stk[tp] != l){
            G[stk[tp]].pb(l);G[l].pb(stk[tp]);
            del.pb(l);stk[tp] = l;
        }
        stk[++tp] = u;
    }
    FOR(i,2,tp) G[stk[i-1]].pb(stk[i]),G[stk[i]].pb(stk[i-1]);
    dfs2(1,0);
    printf("%lld\n",F[1]);
    FOR(i,0,(int)del.size()-1) F[del[i]] = key[del[i]] = 0,G[del[i]].clear();
}

signed main(){
//    freopen("a.in","r",stdin);
    scanf("%lld",&n);
    FOR(i,1,n-1){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    mn[1] = 1e18;dep[1] = 1;
    dfs1(1);int q;scanf("%lld",&q);
    while(q--){
        node.clear();
        int k;scanf("%lld",&k);
        FOR(i,1,k){
            int x;scanf("%lld",&x);
            node.pb(x);
        }
        Solve();
    }
    return 0;
}

/*
 * Time: 2019-11-14 18:15:43
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
#define P std::pair<LL,LL>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;
std::vector<P> G[MAXN];
int val[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int dfn[MAXN],low[MAXN],n,tot;
bool ins[MAXN];
int stk[MAXN],tp;
int col[MAXN],du[MAXN];

inline void dfs(int v){
    static int ts = 0;stk[++tp] = v;
    dfn[v] = low[v] = ++ts;ins[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        ++tot;int t = -1;
        do{
            t = stk[tp--];
            col[t] = tot;
            ins[t] = false;
        }while(t != v);
    }
}

int p1[MAXN],pre[MAXN];

inline int calc(int x){// t <= (x+1)/2
    int p = std::lower_bound(p1+1,p1+100000+1,x)-p1;
    if(p1[p] >= x) p--;
    return x*(p+1)-pre[p];
}

inline void rebuild(){
    FOR(v,1,n){
        for(int i = head[v];i;i = e[i].nxt){
            if(col[v] == col[e[i].to]) val[col[v]] += calc(e[i].w);
            else G[col[v]].pb(MP(col[e[i].to],e[i].w)),du[col[e[i].to]]++;
        }
    }
}

int f[MAXN],S;
bool vis[MAXN];

inline void dfs2(int v){
    vis[v] = 1;
    FOR(i,0,(int)G[v].size()-1){
        P x = G[v][i];
        if(vis[x.fi]) continue;
        dfs2(x.fi);
    }
}

inline void topsort(){
    std::queue<int> q;
    dfs2(col[S]);
    FOR(v,1,tot) if(!vis[v]){
        FOR(i,0,(int)G[v].size()-1){
            du[G[v][i].fi]--;
        }
    }
//    FOR(i,1,n) DEBUG(du[col[i]]);
    FOR(i,1,tot) if(!du[i] && vis[i]) q.push(i);
    int ans = 0;
    while(!q.empty()){
        int v = q.front();q.pop();
        f[v] += val[v];
        ans = std::max(ans,f[v]);
        FOR(i,0,(int)G[v].size()-1){
            P x = G[v][i];
            int to = x.fi,w = x.se;
            if(!vis[to]) continue;
            f[to] = std::max(f[to],w+f[v]);
            if(!--du[to]) q.push(to);
        }
    }
    printf("%lld\n",ans);
}

inline int dp(int v){
    if(f[v] != -1) return f[v];
    int ans = 0;
    FOR(i,0,(int)G[v].size()-1){
        int to = G[v][i].fi,w = G[v][i].se;
        ans = std::max(ans,dp(to)+w);
    }
    ans += val[v];
    return f[v] = ans;
}

signed main(){int m;
    FOR(i,1,1e5) p1[i] = p1[i-1]+i,pre[i] = pre[i-1]+p1[i];
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    FOR(i,1,n) if(!dfn[i]) dfs(i);
    scanf("%lld",&S);rebuild();
//    FOR(i,1,n) DEBUG(col[i]);
//    topsort();
    CLR(f,-1);
    printf("%lld\n",dp(col[S]));
    return 0;
}

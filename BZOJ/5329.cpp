#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+500;

std::vector<int> G[MAXN],G1[MAXN],G2[MAXN];

int low[MAXN],dfn[MAXN],stk[MAXN],top,cnt,n,m;

inline void Tarjan(int v){
    static int ts = 0;
    low[v] = dfn[v] = ++ts;
    stk[++top] = v;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(!dfn[x]){
            Tarjan(x);
            low[v] = std::min(low[x],low[v]);
            if(low[x] >= dfn[v]){
                G1[v].pb(n+(++cnt));
                int t = -1;
                do{
                    t = stk[top--];
                    G1[n+cnt].pb(t);
                }while(t != x);
            }
        }
        else low[v] = std::min(low[v],dfn[x]);
    }
}

int f[MAXN][21],dep[MAXN],pre[MAXN];

inline void dfs1(int v,int fa=0){
    static int ts = 0;
    dfn[v] = ++ts;
    FOR(i,1,20) f[v][i] = f[f[v][i-1]][i-1];
    FOR(i,0,(int)G1[v].size()-1){
        int x = G1[v][i];
        if(x != fa){
            dep[x] = dep[v] + 1;
            pre[x] = pre[v]+(x<=n);
            f[x][0] = v;dfs1(x,v);
        }
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,20) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,20,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

bool sp[MAXN];
int g[MAXN];

inline int calc(int x,int y){
    return pre[y]-pre[x]-(y<=n);
}

inline int dfs2(int v){
    g[v] = 0;
    FOR(i,0,(int)G2[v].size()-1){
        int x = G2[v][i];
        g[v] += dfs2(x)+calc(v,x);
    }
    if(!sp[v] && v <= n && (v != 1 || G2[v].size() != 1)) g[v]++;
    if(v == 1 && G2[v].size() == 1 && !sp[v]) g[v] -= calc(v,G2[v][0]);
    return g[v];
}

inline bool cmp(int x,int y){
    return dfn[x] < dfn[y];
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,(n<<1)){
        G[i].clear();G1[i].clear();G2[i].clear();
    }
    ::cnt = 0;
    CLR(dfn,0);CLR(low,0);CLR(dep,0);CLR(f,0);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    Tarjan(1);
    pre[1] = dep[1] = 1;dfs1(1);
    int q,cnt=0;scanf("%d",&q);
    static int a[MAXN],rec[MAXN];
    while(q--){
        scanf("%d",&m);
        FOR(i,1,m) scanf("%d",a+i);
        std::sort(a+1,a+m+1,cmp);
        stk[top=1]=1;cnt = 0;
        for(int j = (a[1]==1?2:1);j <= m;++j){
            while(lca(stk[top],a[j]) != stk[top]){
                int l = lca(stk[top],a[j]);
                if(dep[l] > dep[stk[top-1]]){
                    G2[l].pb(stk[top]);
                    rec[++cnt] = stk[top],stk[top] = l;
                }
                else{
                    G2[stk[top-1]].pb(stk[top]);
                    rec[++cnt] = stk[top--];
                }
            }
            stk[++top] = a[j];
        }
        while(top>1){
            G2[stk[top-1]].pb(stk[top]);
            rec[++cnt] = stk[top--];
        }
        rec[++cnt] = 1;
        FOR(i,1,m) sp[a[i]] = true;
        printf("%d\n",dfs2(1));
        FOR(i,1,cnt) sp[rec[i]] = false,G2[rec[i]].clear();
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

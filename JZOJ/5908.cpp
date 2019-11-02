/*
 * Author: RainAir
 * Time: 2019-10-29 10:02:33
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

const int MAXN = 2e5 + 5;
struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,q;
LL val[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int sz[MAXN],nfd[MAXN],son[MAXN],tp[MAXN],dep[MAXN],fa[MAXN],dfn[MAXN];
inline void dfs1(int v,int fa=0){
    sz[v] = 1;
    ::fa[v] = fa;
    for(int i = head[v];i;i = e[i].nxt){
        int x = e[i].to;
        if(x == fa) continue;
        dep[x] = dep[v] + 1;
        dfs1(x,v);sz[v] += sz[x];
        if(sz[son[v]] < sz[x]) son[v] = x;
    }
}

inline void dfs2(int v,int tp){
    static int ts = 0;
    ::tp[v] = tp;
    dfn[v] = ++ts;nfd[ts] = v;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].nxt){
        int x = e[i].to;
        if(x == son[v] || x == fa[v]) continue;
        dfs2(x,x);
    }
}

LL sm[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    sm[x] = sm[lc] + sm[rc];
}

inline void build(int x,int l,int r){
    if(l == r){
        sm[x] = val[nfd[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void update(int x,int l,int r,int ps,LL d){
    if(l == r){
        sm[x] = d;
        return;
    }
    int mid = (l + r) >> 1;
    if(ps <= mid) update(lc,l,mid,ps,d);
    else update(rc,mid+1,r,ps,d);
    pushup(x);
}

inline LL query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

inline LL query(int u,int v){
    LL res = 0;
    while(tp[u] != tp[v]){
        if(dep[tp[u]] < dep[tp[v]]) std::swap(u,v);
        res += query(1,1,n,dfn[tp[u]],dfn[u]);
        u = fa[tp[u]];
    }
    if(dep[u] > dep[v]) std::swap(u,v);
    res += query(1,1,n,dfn[u],dfn[v]);
    return res;
}

inline int lca(int u,int v){
    if(!u || !v) return 0;
    while(tp[u] != tp[v]){
        if(dep[tp[u]] < dep[tp[v]]) std::swap(u,v);
        u = fa[tp[u]];
    }
    if(dep[u] > dep[v]) std::swap(u,v);
    return u;
}

std::vector<int> node;
int cf[MAXN];

inline void dfs3(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs3(e[i].to,v);cf[v] += cf[e[i].to];
    }
}

inline void Solve(){
    FOR(i,1,n) cf[i] = 0;
    FOR(i,0,(int)node.size()-1){
        FOR(j,i+1,(int)node.size()-1){
            int x = node[i],y = node[j];
            int l = lca(x,y);
            cf[x]++;cf[y]++;cf[l]--;cf[fa[l]]--;
        }
    }
    dfs3(1);LL ans = 0;
    FOR(i,1,n) if(cf[i]) ans += val[i];
    printf("%lld\n",ans);
}

inline bool cmp(int x,int y){
    return dfn[x] < dfn[y];
}

std::vector<int> G[MAXN],ver;
int stk[MAXN],top;
LL res;

inline void dfs4(int v,int fa=0){
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(x == fa) continue;
        res += query(v,G[v][i]);
        dfs4(x,v);
    }
}

inline void reSolve(){
    std::sort(all(node),cmp);ver.clear();
    stk[top = 1] = 0;ver.pb(0);
    FOR(i,0,(int)node.size()-1){
        ver.pb(node[i]);
        int u = node[i],l = lca(u,stk[top]);
        if(l == stk[top]) stk[++top] = u;
        else{
            while(top-1 >= 1 && dep[stk[top-1]] >= dep[l]){
                G[stk[top-1]].pb(stk[top]);
                G[stk[top]].pb(stk[top-1]);
                top--;
            }
            if(stk[top] != l){
                G[stk[top]].pb(l);
                G[l].pb(stk[top]);
                stk[top] = l;
                ver.pb(l);
            }
            stk[++top] = u;
        }
    }
    res = 0;
    FOR(i,2,top) G[stk[i]].pb(stk[i-1]),G[stk[i-1]].pb(stk[i]);
    dfs4(G[0][0]);
    FOR(i,0,(int)ver.size()-1){
        int x = ver[i];
        int t = G[x].size();t = std::max(0,t-1);
        if(x == G[0][0]) t = std::max(0,t-1);
        res -= t*val[x];
    }
    printf("%lld\n",res);
    FOR(i,0,(int)ver.size()-1){
        int x = ver[i];
        G[x].clear();
    }
}

int main(){
    freopen("kaihuang.in","r",stdin);
    freopen("kaihuang.out","w",stdout);
    scanf("%d%d",&n,&q);
    FOR(i,1,n) scanf("%lld",val+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dep[1] = 1;dfs1(1);dfs2(1,1);
    build(1,1,n);
    char ch[5];
    FOR(i,1,q){
        scanf("%s",ch);
        if(ch[0] == 'Q'){
            node.clear();
            int t=0;
            do{
                scanf("%d",&t);
                if(t) node.pb(t);
            }while(t);
            if(node.size() == 1){
                printf("%lld\n",val[node[0]]);
            }
            else if(node.size() == 2){
                printf("%lld\n",query(node[0],node[1]));
            }
            else{
                reSolve();
            }
        }
        else{
            int x;LL y;scanf("%d%lld",&x,&y);
            val[x] = y;update(1,1,n,dfn[x],y);
        }
    }
    return 0;
}

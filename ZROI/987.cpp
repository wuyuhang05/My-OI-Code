/*
 * Author: RainAir
 * Time: 2019-09-13 19:01:12
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

const int MAXN = 100000+5;

struct Edge{
    int to,next;
}e[MAXN<<1];
int head[MAXN],val[MAXN],cnt;
int sum[MAXN<<2],n,m;
int size[MAXN],top[MAXN],dfn[MAXN],fa[MAXN],son[MAXN],id[MAXN],dep[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

void dfs1(int v){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v]) continue;
        dep[e[i].to] = dep[v]+1;
        fa[e[i].to] = v;dfs1(e[i].to);
        size[v] += size[e[i].to];
        if(size[e[i].to] > size[son[v]]) son[v] = e[i].to;
    }
}

void dfs2(int v,int tp){
    static int ts = 0;
    top[v] = tp;dfn[v] = ++ts;id[ts] = v;
    if(son[v]) dfs2(son[v],tp);
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa[v] || e[i].to == son[v]) continue;
        dfs2(e[i].to,e[i].to);
    }
}

#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
    sum[x] = sum[lc] + sum[rc];
}

inline void build(int x,int l,int r){
    if(l == r){
        sum[x] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void update(int x,int l,int r,int pos){
    if(l == r){
        sum[x]++;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos);
    else update(rc,mid+1,r,pos);
    pushup(x);
}

inline int qsum(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sum[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return qsum(lc,l,mid,L,R);
    if(L > mid) return qsum(rc,mid+1,r,L,R);
    return qsum(lc,l,mid,L,mid) + qsum(rc,mid+1,r,mid+1,R);
}

inline int calc(int x,int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        ans += qsum(1,1,n,dfn[top[x]],dfn[x]);//DEBUG(ans);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return ans + qsum(1,1,n,dfn[x],dfn[y]);
}

inline int lca(int x,int y){
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return x;
}

P q[MAXN];
LL ans = 0;
int g[MAXN];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dep[1] = 1;dfs1(1);dfs2(1,1);build(1,1,n);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        int l = lca(u,v);++g[l];
        update(1,1,n,dfn[l]);
        q[i] = MP(u,v);
    }
    LL ans = 0;
    FOR(i,1,m){
        ans += calc(q[i].fi,q[i].se) - 1;
    }
    FOR(i,1,n) ans -= g[i]*(g[i]-1)/2;
    printf("%lld\n",ans);
    return 0;
}


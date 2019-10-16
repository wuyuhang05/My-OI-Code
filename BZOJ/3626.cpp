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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define Re register
#define rc (x<<1|1)
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 50000+5;
const int ha = 201314;

struct Edge{
    int to,next;
}e[MAXN<<2];
int head[MAXN],dfn[MAXN],id[MAXN],dep[MAXN],top[MAXN],son[MAXN],size[MAXN],fa[MAXN],cnt;

inline void link(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

inline void add(int &x,int y){
    x += y;while(x < 0) x += ha;
    while(x > ha) x -= ha;
}

void dfs1(int u){
    size[u] = 1;
    for(int i = head[u];i;i = e[i].next){
        int v;if((v = e[i].to) == fa[u]) continue;
        dep[v] = dep[u]+1;//fa[v] = u;
        dfs1(v);
        size[u] += size[v];if(size[v] > size[son[u]]) son[u] = v;
    }
}

void dfs2(int u,int tp){
    static int ts = 0;
    dfn[u] = ++ts;id[ts] = u;top[u] = tp;
    if(son[u]) dfs2(son[u],tp);
    for(int i = head[u];i;i = e[i].next){
        int v = e[i].to;if(v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}

int sum[MAXN<<2],tag[MAXN<<2];

void pushup(int x){
    //sum[x] = sum[lc] + sum[rc];
    sum[x] = 0;add(sum[x],sum[lc]);add(sum[x],sum[rc]);
}

void cover(int x,int l,int r,int delta){
    //sum[x] += (r-l+1)*delta;
    add(sum[x],(r-l+1)*delta);
    //tag[x] += delta;
    add(tag[x],delta);
}

void pushdown(int x,int l,int r){
    if(tag[x]){
        int mid = (l + r) >> 1;
        cover(lc,l,mid,tag[x]);
        cover(rc,mid+1,r,tag[x]);
        tag[x] = 0;
    }
}

void modify(int x,int l,int r,int L,int R){
    if(l == L && r == R){
        cover(x,l,r,1);return;
    }
    pushdown(x,l,r);
    int mid = (l + r) >> 1;
    if(R <= mid) modify(lc,l,mid,L,R);
    else if(L > mid) modify(rc,mid+1,r,L,R);
    else modify(lc,l,mid,L,mid),modify(rc,mid+1,r,mid+1,R);
    pushup(x);
}

int query(int x,int l,int r,int L,int R){
    // DEBUG(x);
    if(l == L && r == R) return sum[x];
    pushdown(x,l,r);
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return (query(lc,l,mid,L,mid) + query(rc,mid+1,r,mid+1,R)) % ha;
}

int N,M;

inline void upd(int v){
    while(v){
        modify(1,1,N,dfn[top[v]],dfn[v]);
        v = fa[top[v]];
    }
}

inline int calc(int v){
    int ans = 0;
    while(v){
        // ans += query(1,1,N,dfn[top[v]],dfn[v]);
        add(ans,query(1,1,N,dfn[top[v]],dfn[v]));
        v = fa[top[v]];
    }
    return ans;
}

int z[MAXN],ans[MAXN];
std::vector<int> q1[MAXN],q2[MAXN];

signed main(){
    scanf("%lld%lld",&N,&M);
    FOR(i,2,N){
        scanf("%lld",fa+i);link(++fa[i],i);
    }
    dep[1] = 1;dfs1(1),dfs2(1,1);
    FOR(i,1,M){
        int l,r;scanf("%lld%lld%lld",&l,&r,z+i);
        q2[l].push_back(i);q1[r+1].push_back(i);++z[i];
    }
    FOR(i,1,N){
        upd(i);
        FOR(j,0,(int)q1[i].size()-1) add(ans[q1[i][j]],calc(z[q1[i][j]]));
        FOR(j,0,(int)q2[i].size()-1) add(ans[q2[i][j]],-calc(z[q2[i][j]]));
    }
    FOR(i,1,M) printf("%lld\n",ans[i]+ha%ha);
    //system("pause");
    return 0;
}

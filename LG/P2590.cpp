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

#define lc (x<<1)
#define rc (x<<1|1)
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

const int MAXN = 30000+5;

struct Edge{
    int to,next;
}e[MAXN<<1];
int head[MAXN],val[MAXN],cnt;
int sum[MAXN<<2],max[MAXN<<2];
int size[MAXN],top[MAXN],dfn[MAXN],fa[MAXN],son[MAXN],id[MAXN],dep[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
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

inline void pushup(int x){
    sum[x] = sum[lc] + sum[rc];
    max[x] = std::max(max[lc],max[rc]);
}

inline void build(int x,int l,int r){
    if(l == r){
        sum[x] = max[x] = val[id[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline void update(int x,int l,int r,int pos,int value){
    if(l == r){
        sum[x] = max[x] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos,value);
    else update(rc,mid+1,r,pos,value);
    pushup(x);
}

inline int qsum(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sum[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return qsum(lc,l,mid,L,R);
    if(L > mid) return qsum(rc,mid+1,r,L,R);
    return qsum(lc,l,mid,L,mid) + qsum(rc,mid+1,r,mid+1,R);
}

inline int qmax(int x,int l,int r,int L,int R){
    if(l == L && r == R) return max[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return qmax(lc,l,mid,L,R);
    if(L > mid) return qmax(rc,mid+1,r,L,R);
    return std::max(qmax(lc,l,mid,L,mid),qmax(rc,mid+1,r,mid+1,R));
}

int N,M;

inline void upd(int pos,int x){
    update(1,1,N,dfn[pos],x);
}

inline int casum(int x,int y){
    int ans = 0;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        // DEBUG(x);DEBUG(y);DEBUG(top[x]);
        ans += qsum(1,1,N,dfn[top[x]],dfn[x]);//DEBUG(ans);
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    // DEBUG(x);DEBUG(y);DEBUG(dfn[x]);DEBUG(dfn[y]);
    return ans + qsum(1,1,N,dfn[x],dfn[y]);
}

inline int camax(int x,int y){
    int ans = INT_MIN;
    while(top[x] != top[y]){
        if(dep[top[x]] < dep[top[y]]) std::swap(x,y);
        ans = std::max(ans,qmax(1,1,N,dfn[top[x]],dfn[x]));
        x = fa[top[x]];
    }
    if(dep[x] > dep[y]) std::swap(x,y);
    return std::max(ans,qmax(1,1,N,dfn[x],dfn[y]));
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);add(u,v);add(v,u);
    }
    FOR(i,1,N) scanf("%d",val+i);
    dep[1] = 1;dfs1(1);dfs2(1,1);build(1,1,N);
    scanf("%d",&M);
    //FOR(i,1,N) printf("%d ",dfn[i]);puts("");
    while(M--){
        int x,y;char opt[sizeof("CHANGE")+2];
        scanf("%s%d%d",opt,&x,&y);
        if(opt[1] == 'H') upd(x,y);
        if(opt[1] == 'M') printf("%d\n",camax(x,y));
        if(opt[1] == 'S') printf("%d\n",casum(x,y));
    }
    return 0;
}
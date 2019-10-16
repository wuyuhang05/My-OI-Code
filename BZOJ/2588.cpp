/*
 * Author: RainAir
 * Time: 2019-10-03 19:41:37
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

const int MAXN = 1e5 + 5;
const int MAXM = 19;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int a[MAXN],b[MAXN],ori[MAXN],f[MAXN][MAXM+1],dep[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,MAXM) if(d&(1<<i)) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,MAXM,0) f[x][i] == f[y][i] ? 0 : (x = f[x][i],y = f[y][i],0);
    return f[x][0];
}

int tot = 0;
int root[MAXN],sm[(MAXN<<5)+3],lc[(MAXN<<5)+3],rc[(MAXN<<5)+3];
int n,m,la;

inline void insert(int prev,int &v,int l,int r,int p){
    v = ++tot;sm[v] = sm[prev]+1;lc[v] = lc[prev],rc[v] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc[prev],lc[v],l,mid,p);
    else insert(rc[prev],rc[v],mid+1,r,p);
}

inline int query(int x,int y,int z,int w,int l,int r,int k){
    if(l == r) return l;
    int t = sm[lc[x]]+sm[lc[y]]-sm[lc[z]]-sm[lc[w]];
    int mid = (l + r) >> 1;
    if(k <= t) return query(lc[x],lc[y],lc[z],lc[w],l,mid,k);
    else return query(rc[x],rc[y],rc[z],rc[w],mid+1,r,k-t);
}

inline void dfs(int v,int fa=0){
    f[v][0] = fa;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        insert(root[v],root[e[i].to],1,n,a[e[i].to]);
        dfs(e[i].to,v);
    }
}

inline void build(int &x,int l,int r){
    if(!x) x = ++tot;
    if(l == r){
        sm[x] = (l == a[1]);
        return;
    }
    int mid = (l + r) >> 1;
    build(lc[x],l,mid);build(rc[x],mid+1,r);
    sm[x] = sm[lc[x]]+sm[rc[x]];
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) scanf("%d",a+i),b[i] = a[i];
    std::sort(b+1,b+n+1);int sz = std::unique(b+1,b+n+1)-b;
    FOR(i,1,n) a[i] = std::lower_bound(b+1,b+sz+1,a[i])-b;
    //FOR(i,1,n) DEBUG(a[i]);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dep[1] = 1;build(root[1],1,n);
//    DEBUG(query(root[1],0,0,0,1,n,1));areturn 0;
    dfs(1);//DEBUG(query(root[2],0,0,0,1,n,2));
    FOR(i,1,m){
        int u,v,k;scanf("%d%d%d",&u,&v,&k);u ^= la;
        int l = lca(u,v);
        printf("%d\n",la = b[query(root[u],root[v],root[l],root[f[l][0]],1,n,k)]);
    }
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-07 16:05:21
 */
#include <algorithm>
#include <iostream>
#include <assert.h>
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

inline char nc(){
    #define SIZE 300000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    char ch = nc();x = 0;int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

const int MAXN = 2e5 + 5;
const int MAXM = 5e5 + 5;

std::vector<int> G[MAXN];
struct Edge{
    int u,v,w;
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXM];

int n,m,q;
int f[MAXN],val[MAXN],tot;

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void Union(int x,int y){
    int fx = find(x),fy = find(y);
    if(fx == fy) return;
    f[fx] = f[fy] = ++tot;
    G[tot].pb(fx);G[tot].pb(fy);
    G[fx].pb(tot);G[fy].pb(tot);
}

inline void Kruskal(){
    std::sort(e+1,e+m+1);
    FOR(i,1,2*n) f[i] = i;tot = n;
    FOR(i,1,m){
        int u = e[i].u,v = e[i].v;
        int fu = find(u),fv = find(v);
        if(fu == fv) continue;
        Union(fu,fv);val[tot] = e[i].w;
    }
}

const int MAXL = 18;
int dfn[MAXN],sz[MAXN],dep[MAXN],F[MAXN][MAXL+1],nfd[MAXN];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    FOR(i,1,MAXL) F[v][i] = F[F[v][i-1]][i-1];
    sz[v] = 1;dfn[v] = ++ts;nfd[dfn[v]] = v;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(x == fa) continue;
        F[x][0] = v;dep[x] = dep[v] + 1;dfs(x,v);
        sz[v] += sz[x];
    }
}

inline int getfa(int x,int p){
    ROF(i,MAXL,0) if(dep[x] > (1<<i) && val[F[x][i]] <= p) x = F[x][i];
    return x;
}

int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],cnt;

inline void insert(int prev,int &v,int l,int r,int p,int d){
    sm[v = ++cnt] = sm[prev] + d;lc[v] = lc[prev];rc[v] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) insert(lc[prev],lc[v],l,mid,p,d);
    else insert(rc[prev],rc[v],mid+1,r,p,d);
}

inline int query(int x,int y,int l,int r,int k){
    if(l == r) return l;
    int mid = (l + r) >> 1;
    int ls = sm[lc[y]]-sm[lc[x]];
    //DEBUG(l);DEBUG(r);DEBUG(ls);
    if(k <= ls) return query(lc[x],lc[y],l,mid,k);
    else return query(rc[x],rc[y],mid+1,r,k-ls);
}

int h[MAXN];
std::vector<int> S;
/*
inline void deb(int v){
    if(v <= n) printf("%d ",h[v]);
    for(auto x:G[v]){
        if(dep[x] > dep[v]) deb(x);
    }
}
*/
inline void get(int x,int y,int l,int r){
    if(l == r){
        if(sm[y]-sm[x] > 0) printf("%d ",l);
        return;
    }
    int mid = (l + r) >> 1;
    get(lc[x],lc[y],l,mid);
    get(rc[x],rc[y],mid+1,r);
}

int main(){
   // freopen("1.in","r",stdin);
   // freopen("1.ans","w",stdout);
    read(n);read(m);read(q);
    FOR(i,1,n) read(h[i]),S.pb(h[i]);
    std::sort(all(S));std::unique(all(S));
    FOR(i,1,n) h[i] = std::lower_bound(all(S),h[i])-S.begin() + 1;
    FOR(i,1,m) read(e[i].u),read(e[i].v),read(e[i].w);//,DEBUG(e[i].w);
    Kruskal();dep[tot] = 1;dfs(tot);
//    FOR(i,2,n) assert(find(i) == find(i-1));
    FOR(i,1,tot) insert(root[i-1],root[i],1,n,h[nfd[i]],h[nfd[i]] ? 1 : 0);
    int la = 0;
    //get(24,73,1,n);
    FOR(i,1,q){
        int v,x,k;//la = std::max(la,0);
        read(v);read(x);read(k);
        v ^= la;x ^= la;k ^= la;
        int rt = getfa(v,x);
//        DEBUG(root[dfn[rt]+sz[rt]-1]);
  //      DEBUG(root[dfn[rt]]);
        int len = sm[root[dfn[rt]+sz[rt]-1]]-sm[root[std::max(0,dfn[rt]-1)]];
        if(len < k) puts("-1"),la = 0;
        else printf("%d\n",la = S[query(root[std::max(0,dfn[rt]-1)],root[dfn[rt]+sz[rt]-1],1,n,len-k+1)-1]);
    }
    return 0;
}



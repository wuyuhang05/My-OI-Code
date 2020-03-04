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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e5 + 5;
int a[MAXN],n,m;
#define lc (x<<1)
#define rc (x<<1|1)
struct Matrix{
    LL a[2][2];
    Matrix(){
        //FOR(i,0,1) FOR(j,0,1) a[i][j] = INT_MIN;
        CLR(a,0);
    }

    Matrix operator * (const Matrix &t) const {
        Matrix res;
        FOR(i,0,1){
            FOR(j,0,1){
                FOR(k,0,1) res.a[i][j] = std::max(res.a[i][j],a[i][k]+t.a[k][j]);
            }
        }
        return res;
    }
}last,newm,val[MAXN],sm[MAXN<<2];

std::vector<int> G[MAXN];
int fa[MAXN],sz[MAXN],dep[MAXN],dfn[MAXN],edfn[MAXN],son[MAXN],tp[MAXN],id[MAXN];

inline void dfs1(int v,int faa=0){
    sz[v] = 1;fa[v] = faa;
    for(auto x:G[v]){
        if(x == faa) continue;
        dep[x] = dep[v] + 1;dfs1(x,v);
        sz[v] += sz[x];
        if(!son[v] || sz[son[v]] < sz[x]) son[v] = x;
    }
}

inline void dfs2(int v,int t=1,int fa=0){
    static int ts = 0;dfn[v] = ++ts;id[ts] = v;
    edfn[t] = ts;tp[v] = t;
    // if(v == son[fa]) tp[v] = t;
    // else tp[v] = v;
    if(son[v]) dfs2(son[v],t,v);
    for(auto x:G[v]){
        if(x == fa || x == son[v]) continue;
        dfs2(x,x,v);
    }
}

inline void split(int rt){
    dep[1] = 1;dfs1(rt);dfs2(rt);
}

int lf[MAXN][2],f[MAXN][2];

inline void dfs3(int v,int fa=0){
    lf[v][1] = a[v];
    for(auto x:G[v]){
        if(x == fa || x == son[v]) continue;
        dfs3(x,v);
        // upd lf
        lf[v][0] += std::max(f[x][1],f[x][0]);
        lf[v][1] += f[x][0];
    }
    f[v][0] += lf[v][0];f[v][1] += lf[v][1];
    if(!son[v]) return;
    dfs3(son[v],v);
    f[v][0] += std::max(f[son[v]][0],f[son[v]][1]);
    f[v][1] += f[son[v]][0];
}

inline void pushup(int x){
    sm[x] = sm[lc]*sm[rc];
}

inline void build(int x,int l,int r){
    if(l == r){
        val[id[l]].a[0][0] = lf[id[l]][0];val[id[l]].a[0][1] = lf[id[l]][0];
        val[id[l]].a[1][0] = lf[id[l]][1];val[id[l]].a[1][1] = -1e18;
        sm[x] = val[id[l]];
        return;
    }
    int mid = (l + r) >> 1;
    build(lc,l,mid);build(rc,mid+1,r);
    pushup(x);
}

inline Matrix query(int x,int l,int r,int L,int R){
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc,l,mid,L,R);
    if(L > mid) return query(rc,mid+1,r,L,R);
    return query(lc,l,mid,L,mid)*query(rc,mid+1,r,mid+1,R);
}

inline void update(int x,int l,int r,int pos){
    if(l == r && l == pos){
        sm[x] = val[id[pos]];return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos);
    else update(rc,mid+1,r,pos);
    pushup(x);
}

inline void change(int v,int w){
    val[v].a[1][0] += w - a[v];a[v] = w;
    while(v){
        int t = tp[v];
        last = query(1,1,n,dfn[t],edfn[t]);
        update(1,1,n,dfn[v]);
        newm = query(1,1,n,dfn[t],edfn[t]);
        v = fa[t];
        val[v].a[0][0] += std::max(newm.a[0][0],newm.a[1][0])-std::max(last.a[0][0],last.a[1][0]);
        val[v].a[0][1] = val[v].a[0][0];
        val[v].a[1][0] += newm.a[0][0] - last.a[0][0];
    }
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n-1){
        int u,v;scanf("%lld%lld",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    split(1);dfs3(1);build(1,1,n);
    FOR(i,1,m){
        int x,y;scanf("%lld%lld",&x,&y);change(x,y);
        Matrix ans = query(1,1,n,dfn[1],edfn[1]);
        printf("%lld\n",std::max(ans.a[0][0],ans.a[1][0]));
    }
    return 0;
}


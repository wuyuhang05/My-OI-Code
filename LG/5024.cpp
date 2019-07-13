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

inline char nc(){
    #define SIZE 100000+5
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;char ch = nc();
    while(!isdigit(ch)) ch = nc();
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
}

inline void read(LL &x){
    x = 0;char ch = nc();
    while(!isdigit(ch)) ch = nc();
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
}

const int MAXN = 100000+5;
const LL MIN = -1e15;
std::vector<int> G[MAXN];
int n,m;LL a[MAXN];

#define lc (x<<1)
#define rc (x<<1|1)

struct Matrix{
    LL a[2][2];
    Matrix(){CLR(a,0);}

    inline Matrix operator * (const Matrix &t) const {
        Matrix res;
        FOR(i,0,1){
            FOR(j,0,1){
                FOR(k,0,1) res.a[i][j] = std::max(res.a[i][j],a[i][k]+t.a[k][j]);
            }
        }
        return res;
    }
}val[MAXN],sm[MAXN<<2],lst,now;

int fa[MAXN],dfn[MAXN],nfd[MAXN],id[MAXN],dep[MAXN],sz[MAXN],son[MAXN],tp[MAXN];
LL f[MAXN][2],lf[MAXN][2];

inline void dfs1(int v,int faa=0){
    fa[v] = faa;sz[v] = 1;
    for(auto x:G[v]){
        if(x == faa) continue;
        dep[x] = dep[v] + 1;dfs1(x,v);
        sz[v] += sz[x];
        if(!son[v] || sz[son[v]] < sz[x]) son[v] = x;
    }
}

inline void dfs2(int v,int t=1,int fa=0){
    static int ts = 0;dfn[v] = ++ts;nfd[t] = ts;
    id[ts] = v;tp[v] = t;
    if(son[v]) dfs2(son[v],t,v);
    for(auto x:G[v]){
        if(x == fa || x == son[v]) continue;
        dfs2(x,x,v);
    }
}

inline void dfs3(int v,int fa=0){
    lf[v][1] = a[v];
    for(auto x:G[v]){
        if(x == fa || x == son[v]) continue;
        dfs3(x,v);
        lf[v][0] += std::max(f[x][1],f[x][0]);
        lf[v][1] += f[x][0];
    }
    f[v][0] += lf[v][0];
    f[v][1] += lf[v][1];
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
        val[id[l]].a[1][0] = lf[id[l]][1];val[id[l]].a[1][1] = MIN;
        sm[x] = val[id[l]];return;
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
        sm[x] = val[id[pos]];
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) update(lc,l,mid,pos);
    else update(rc,mid+1,r,pos);
    pushup(x);
}

inline void change(int v,LL w){
    //val[v].a[1][0] += w-a[v];
    val[v].a[1][0] += w;
    a[v] += w;
    while(v){
        int t = tp[v];
        lst = query(1,1,n,dfn[t],nfd[t]);
        update(1,1,n,dfn[v]);
        now = query(1,1,n,dfn[t],nfd[t]);
        v = fa[t];
        val[v].a[0][0] += std::max(now.a[0][0],now.a[1][0]) - std::max(lst.a[0][0],lst.a[1][0]);
        val[v].a[0][1] = val[v].a[0][0];
        val[v].a[1][0] += now.a[0][0]-lst.a[0][0];
    }
}
LL sum = 0,xx;
std::set<int> S[MAXN];
signed main(){
    read(n);read(m);read(xx);DEBUG(xx);
    FOR(i,1,n) read(a[i]),sum += a[i];
    FOR(i,1,n-1){
        int u,v;read(u);read(v);
        G[u].pb(v);G[v].pb(u);S[u].insert(v);S[v].insert(u);
    }dep[1] = 1;
    dfs1(1);dfs2(1);dfs3(1);build(1,1,n);
    FOR(i,1,m){
        LL a,x,b,y;read(a);read(x);read(b);read(y);//scanf("%lld%lld%lld%lld",&a,&x,&b,&y);
        if(x == 0 && y == 0 && S[a].count(b)){
            puts("-1");continue;
        }
        x = x ? INT_MAX : INT_MIN;y = y ? INT_MAX : INT_MIN;
        x = -x;y = -y;
        change(a,x);change(b,y);
        Matrix res = query(1,1,n,dfn[1],nfd[1]);
        LL ans = std::max(res.a[0][0],res.a[1][0]);
        printf("%lld\n",sum-ans+std::max(x,0ll)+std::max(y,0ll));
        change(a,-x);change(b,-y);
    }
    return 0;
}

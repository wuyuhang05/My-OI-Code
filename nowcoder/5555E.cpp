#include<bits/stdc++.h>

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

const int MAXN = 1e5 + 5;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
    #undef SIZE
}

template <typename T>
inline void read(T &x){
    x = 0;int flag = 0;char ch = nc();
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

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int n,q;

int sm[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;

inline void update(int prev,int &v,int l,int r,int p,int d){
    sm[v = ++tot] = sm[prev]+d;lc[v] = lc[prev];rc[v] = rc[prev];
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(p <= mid) update(lc[prev],lc[v],l,mid,p,d);
    else update(rc[prev],rc[v],mid+1,r,p,d);
}

inline int query(int x,int l,int r,int L,int R){
    if(!x) return 0;
    if(l == L && r == R) return sm[x];
    int mid = (l + r) >> 1;
    if(R <= mid) return query(lc[x],l,mid,L,R);
    if(L > mid) return query(rc[x],mid+1,r,L,R);
    return query(lc[x],l,mid,L,mid)+query(rc[x],mid+1,r,mid+1,R);
}

std::vector<int> ext;
const int MAXM = 16;
const int M = 1e6;
int a[MAXN],ta[MAXN];
int f[MAXN][MAXM+1],dfn[MAXN],sz[MAXN],fa[MAXN],nfd[MAXN],dep[MAXN];
std::vector<int> son[MAXN];

inline int gcd(int x,int y){
    return std::__gcd(x,y);
}

inline void pdfs(int v,int fa=0){
    f[v][0] = fa;sz[v] = 1;::fa[v] = fa;dep[v] = dep[fa]+1;
    static int ts = 0;dfn[v] = ++ts;nfd[ts] = v;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        pdfs(e[i].to,v);sz[v] += sz[e[i].to];
        son[v].pb(dfn[e[i].to]);
    }
    std::sort(all(son[v]));
}

inline void dfs(int v,int fa=0){
    if(fa) update(root[fa],root[v],1,M,gcd(ta[fa],ta[v]),1);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,MAXM) if((d>>i)&1) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}
bool vis[MAXN];
inline void rebuild(){
    FOR(i,1,n) root[i] = vis[i] = 0;tot = 0;
    for(auto x:ext) ta[x] = a[x];
    ext.clear();
    dfs(1);
}
std::unordered_map<int,int> S;
inline int calc(int v,int k){
//    DEBUG(v);
    int res = query(root[v],1,M,1,k);
    S.clear();
    for(auto x:ext){
        if(dfn[x] <= dfn[v] && dfn[x]+sz[x]-1 >= dfn[v]){
            if(fa[x]){
                if(S[x]) continue;
                S[x] = 1;
                res -= gcd(ta[x],ta[fa[x]]) <= k;
                res += gcd(a[x],a[fa[x]]) <= k;
            }
            if(x != v){
                int t = std::upper_bound(all(son[x]),dfn[v])-son[x].begin()-1;
                t = nfd[son[x][t]];
                if(S[t]) continue;
                S[t] = 1;
                res -= gcd(ta[t],ta[fa[t]]) <= k;
                res += gcd(a[t],a[fa[t]]) <= k;
            }
        }
    }
    return res;
}

int main(){
//    freopen("test.in","r",stdin);
//    freopen("test1.out","w",stdout);
    read(n);read(q);
    FOR(i,1,n) read(a[i]),ta[i] = a[i];
    FOR(i,2,n){
        int u,v;read(u);read(v);
        add(u,v);
    }
    pdfs(1);rebuild();int LIM = std::sqrt(1.0*n);
    FOR(i,1,q){
        int opt;read(opt);
        if(opt == 1){
            int v,x;read(v);read(x);
            a[v] = x;
            if(!vis[v]) ext.pb(v),vis[v] = 1;
            if(ext.size() > LIM) rebuild();
        }
        else{
            int u,v,k;read(u);read(v);read(k);
            printf("%d\n",calc(u,k)+calc(v,k)-2*calc(lca(u,v),k));
        }
    }
    return 0;
}


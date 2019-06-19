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

const int MAXN = 200000+5;
const int MAXM = 10000000+5;
const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

struct BIT{
    #define lowbit(x) (x&-x)
    int tree[MAXN<<1],n;

    inline void init(int size){
        n = size;std::fill(tree+1,tree+n+1,1);
    }

    inline void modify(int pos,int x){
        while(pos <= n){
            tree[pos] = 1ll*tree[pos]*x%ha;
            pos += lowbit(pos);
        }
    }

    inline int calc(int pos){
        int res = 1;
        while(pos){
            res = 1ll*res*tree[pos]%ha;
            pos -= lowbit(pos);
        }
        return res;
    }

    inline int query(int l,int r){
        return 1ll*calc(r)*qpow(calc(l-1),ha-2)%ha;
    }
}bit;

std::vector<int> G[MAXN];
int n,m,val[MAXN],f[MAXN][30],dep[MAXN],dfn[MAXN],ext[MAXN],inv[MAXM],d[MAXM],prime[MAXM],cnt;
std::vector<int> p[MAXN];
std::vector<std::pair<int,int> > q[MAXN];

void dfs(int v){
    static int ts = 0;
    dfn[v] = ++ts;p[dep[v]].pb(v);
    FOR(i,1,20) f[v][i] = f[f[v][i-1]][i-1];
    for(auto to:G[v]){
        if(to != f[v][0]){
            f[to][0] = v;dep[to] = dep[v]+1;
            dfs(to);
        }
    }
    ext[v] = ts;
}

void sieve(int n){
    inv[1] = 1;
    FOR(i,2,n){
        inv[i] = (ha-1ll*(ha/i)*inv[ha%i]%ha)%ha;
        if(!d[i]) prime[++cnt] = d[i] = i;
        for(int j = 1;j <= cnt && prime[j] <= d[i] && i*prime[j] <= n;++j){
            d[i*prime[j]] = prime[j];
        }
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,20) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,20,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i];y = f[y][i];
    }
    return f[x][0];
}

struct Node{
    int x;
    Node(int x=0) : x(x) {}
    bool operator < (const Node &t) const {
        return dfn[x] < dfn[t.x];
    }
};
std::set<Node> S[MAXM];
int ans[MAXN];

inline void insert(int val,int pos){
    auto t = S[val].insert(Node(pos)).first;
    bit.modify(dfn[pos],d[val]);
    auto pre = t,suf = t;
    if(pre != S[val].begin()){
        pre--;int tpos = lca((*t).x,(*pre).x);
        bit.modify(dfn[tpos],inv[d[val]]);
        if(++suf != S[val].end()){
            tpos = lca((*t).x,(*suf).x);
            bit.modify(dfn[tpos],inv[d[val]]);
            tpos = lca((*pre).x,(*suf).x);
            bit.modify(dfn[tpos],d[val]);
        }
    }
    else if(++suf != S[val].end()){
        int tpos = lca((*t).x,(*suf).x);
        bit.modify(dfn[tpos],inv[d[val]]);
    }
}

int main(){
    scanf("%*d%d",&n);
    FOR(i,1,n) scanf("%d",val+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    sieve(1e7);dep[1] = 1;dfs(1);
    scanf("%d",&m);
    FOR(i,1,m){
        int x,y;scanf("%d%d",&x,&y);
        q[std::min(dep[x]+y,n)].pb(MP(x,i));
    }
    bit.init(n);
    FOR(i,1,n){
        for(auto x:p[i]){
            int t = val[x];
            while(t != 1){
                int p = d[t],q = 1;
                while(!(t%p)) q *= p,t /= p,insert(q,x);
            }
        }
        for(auto x:q[i]){
            ans[x.se] = bit.query(dfn[x.fi],ext[x.fi]);
        }
    }
    FOR(i,1,m) printf("%d\n",ans[i]);
    return 0;
}

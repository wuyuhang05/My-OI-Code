#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;

#define fi first
#define se second
#define db double
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

const int MAXN = 5e4 + 5;
const int BASE = 257;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

char str[MAXN];
int n;

int sz[MAXN],mx[MAXN],rt;
bool vis[MAXN];
bool DEB = 0;

inline void getroot(int v,int fa=0){
    sz[v] = 1;mx[v] = 0;int ct = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        getroot(e[i].to,v);sz[v] += sz[e[i].to];
        mx[v] = std::max(mx[v],sz[e[i].to]);
    }
    mx[v] = std::max(mx[v],mx[0]-sz[v]);
    if(mx[rt] > mx[v]) rt = v;
}

int k;
//std::map<U LL,int> S;
gp_hash_table<U LL,int> S;
U LL pw[MAXN];
int dep[MAXN];
U LL sm[MAXN],ms[MAXN];
bool pal[MAXN];

inline void precalc(int v,int fa=0){
    sz[v] = 1;dep[v] = dep[fa]+1;
    sm[v] = sm[fa]*BASE+str[v];
    ms[v] = ms[fa]+str[v]*pw[dep[v]-1];
    pal[v] = sm[v]==ms[v];
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to] || e[i].to == fa) continue;
        precalc(e[i].to,v);sz[v] += sz[e[i].to];
    }
}

inline void dfs(int v,int opt,int fa=0){
    if(dep[v] > k) return;
    S[sm[v]] += opt;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        dfs(e[i].to,opt,v);
    }
}

bool ok;
std::vector<int> node;

inline void calc(int v,int fa=0){
    if(ok) return;
    if(dep[v] > k) return;
    node.pb(v);
    if(dep[v] > k/2){
        if(k-dep[v] == 0){
            ok |= pal[v];
        }
        int t = k-dep[v];
        if(t > 0 && dep[v]-1-t >= 0){
            int nd = node[dep[v]-1-t];
            if(pal[nd]){
                U LL val = sm[v];
                if(dep[v]-1-t-1 >= 0) val -= sm[node[dep[v]-1-t-1]]*pw[t+1];
                if(S[val]) ok = 1;
            }
        }
    }
    if(ok) return;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        calc(e[i].to,v);
    }
    node.pop_back();
}

inline void getans(int v){
//    if(v == 4) DEB = 1;
    S.clear();precalc(v);node.clear();node.pb(v);
    dfs(v,1);
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to]) continue;
        dfs(e[i].to,-1,v);
        calc(e[i].to,v);
        if(ok) return;
        dfs(e[i].to,1,v);
    }
//    if(v == 4) DEB = 0;
}

inline void work(int v){
    if(ok) return;
    vis[v] = 1;getans(v);
    if(ok) return;
    for(int i = head[v];i;i = e[i].nxt){
        if(vis[e[i].to]) continue;
        mx[rt = 0] = sz[e[i].to];
        getroot(e[i].to);
        work(rt);
    }
}

inline bool chk(int k){
    ::k = k;
    FOR(i,1,n) vis[i] = 0;ok = 0;
    mx[rt = 0] = n;getroot(1);
    work(rt);
    return ok;
}

int main(){
    freopen("a.in","r",stdin);
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = pw[i-1]*BASE;
    scanf("%d",&n);
    scanf("%s",str+1);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
//    DEBUG(chk(5));
//    exit(0);
    int res = 1;
    int l = 1,r = (n-1)/2,ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(2*mid+1)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    res = std::max(res,2*ans+1);
    l = 1,r = n/2,ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(2*mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    res = std::max(res,2*ans);
    printf("%d\n",res);
    return 0;
}

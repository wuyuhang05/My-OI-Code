/*
 * Author: RainAir
 * Time: 2019-10-29 19:43:43
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
#define int LL
const int MAXN = 1e5 + 5;
const int MAXM = 19;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int f[MAXN][MAXM+1],sm[MAXN],dep[MAXN],dfn[MAXN],nfd[MAXN];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = ++ts;nfd[ts] = v;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        sm[e[i].to] = sm[v] + e[i].w;
        f[e[i].to][0] = v;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x] - dep[y];
        FOR(i,0,MAXM) if((1<<i)&d) x = f[x][i];
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

inline int calc(int x,int y){
    int l = lca(x,y);
    return sm[x]+sm[y]-2*sm[l];
}

std::set<int> S;
int n,m,res;

inline void insert(int x){
    if(S.empty()){
        S.insert(dfn[x]);
        return;
    }
    std::set<int>::iterator ps = S.lower_bound(dfn[x]);
    if(ps == S.end() || ps == S.begin()){
        res -= calc(nfd[*S.rbegin()],nfd[*S.begin()]);
        res += calc(nfd[*S.rbegin()],x);
        res += calc(x,nfd[*S.begin()]);
        S.insert(dfn[x]);
    }
    else{
        std::set<int>::iterator pre = ps;--pre;
        res -= calc(nfd[*pre],nfd[*ps]);
        res += calc(nfd[*pre],x);
        res += calc(x,nfd[*ps]);
        S.insert(dfn[x]);
    }
}

inline void erase(int x){
    if(S.size() == 1){
        S.erase(dfn[x]);
        return;
    }
    std::set<int>::iterator ps = S.find(dfn[x]);
    if(ps == S.begin()){
        ++ps;
        res += calc(nfd[*S.rbegin()],nfd[*ps]);
        res -= calc(nfd[*S.rbegin()],x);
        res -= calc(x,nfd[*ps]);
        S.erase(dfn[x]);
    }
    else if(*ps == *S.rbegin()){
        --ps;
        res += calc(nfd[*ps],nfd[*S.begin()]);
        res -= calc(nfd[*S.begin()],x);
        res -= calc(nfd[*ps],x);
        S.erase(dfn[x]);
    }
    else{
        std::set<int>::iterator pre = ps;--pre;
        std::set<int>::iterator suf = ps;++suf;
        res += calc(nfd[*pre],nfd[*suf]);
        res -= calc(nfd[*pre],x);
        res -= calc(x,nfd[*suf]);
        S.erase(dfn[x]);
    }
}

signed main(){
   // freopen("1.in","r",stdin);
    freopen("a.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n-1){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    dfs(1);
    FOR(i,1,m){
        int t;scanf("%lld",&t);
        if(S.count(dfn[t])) erase(t);
        else insert(t);
        printf("%lld\n",res);
    }
    return 0;
}

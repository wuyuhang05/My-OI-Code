/*
 * Author: RainAir
 * Time: 2019-09-07 17:49:57
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
const int ha = 1e9 + 7;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int n,head[MAXN],cnt;
std::vector<P> edge;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int dep[MAXN],dfn[MAXN],_[MAXN],sz[MAXN],nfd[MAXN],A,B,C,D;
std::vector<int> S[MAXN];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = ++ts;_[v] = fa;sz[v] = 1;nfd[ts] = v;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;dfs(e[i].to,v);
        sz[v] += sz[e[i].to];
    }
}

inline int calc(int _,int l,int r){
    int ll = std::lower_bound(all(S[_]),l)-S[_].begin();
    int rr = std::upper_bound(all(S[_]),r)-S[_].begin();
    if(S[_][ll] > r) return 0;
    return rr-ll;
}

inline int query(int v,int l1,int l2){
    int sm = 0,ans = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == _[v]) continue;
        int tl = calc(dep[v]+l1,dfn[e[i].to],dfn[e[i].to]+sz[e[i].to]-1);
        int tr = calc(dep[v]+l2,dfn[e[i].to],dfn[e[i].to]+sz[e[i].to]-1);
        (ans += sm*tr%ha) %= ha;
        (sm += tl) %= ha;
    }
    return ans;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n-1){
        int u,v;scanf("%lld%lld",&u,&v);
        edge.pb(MP(u,v));
    }
    std::reverse(all(edge));
    for(auto x:edge) add(x.fi,x.se);
    dep[1] = 1;dfs(1);
    FOR(i,1,n) S[i].pb(-19260817),S[i].pb(19260817);
    FOR(i,1,n) S[dep[i]].pb(dfn[i]);
    FOR(i,1,n) std::sort(all(S[i]));
    scanf("%lld%lld%lld%lld",&A,&B,&C,&D);
    int sm = 0,ans = 0;
    FOR(i,1,n){ // 和 calc 类似的整体询问
        int v = nfd[i];
        int t1 = query(v,A,B),t2 = query(v,C,D);
        (ans += sm*t2%ha)%=ha;(sm += t1) %= ha;
    }
    printf("%lld\n",ans);
    return 0;
}

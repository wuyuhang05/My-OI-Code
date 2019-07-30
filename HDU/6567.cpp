/*
 * Author: RainAir
 * Time: 2019-07-27 18:44:06
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
const int MAXN = 2e5 + 5;
int n;
std::vector<int> G[MAXN];
bool vis[MAXN];
int rt[3],N[3],sz[MAXN];

inline void dfs1(int v,int op){
    vis[v] = true;N[op]++;sz[v] = 1;
    for(auto x:G[v]){
        if(vis[x]) continue;
        dfs1(x,op);sz[v] += sz[x];
    }
}

int mx[MAXN],rtt[3];

inline void dfs2(int v,int fa,int op){
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs2(x,v,op);mx[v] = std::max(mx[v],sz[x]);
    }
    mx[v] = std::max(mx[v],N[op]-sz[v]);
    if(mx[rtt[op]] > mx[v]) rtt[op] = v;
}
LL ans = 0ll;
inline void dfs3(int v,int fa=0){
    sz[v] = 1;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs3(x,v);sz[v] += sz[x];
    }
    ans += sz[v]*(n-sz[v]);
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n-2){
        int u,v;scanf("%lld%lld",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    mx[0] = INT_MAX;
    FOR(i,1,n) if(!vis[i]) rt[++rt[0]] = i,dfs1(i,rt[0]);
    dfs2(rt[1],0,1);dfs2(rt[2],0,2);
   // DEBUG(rtt[1]);DEBUG(rtt[2]);
    G[rtt[1]].pb(rtt[2]);G[rtt[2]].pb(rtt[1]);
 //   FOR(i,1,n) DEBUG(mx[i]);
    //DEBUG(rtt[1]);DEBUG(rtt[2]);
    std::fill(sz,sz+n+1,0);dfs3(1);
    printf("%lld\n",ans);
    return 0;
}

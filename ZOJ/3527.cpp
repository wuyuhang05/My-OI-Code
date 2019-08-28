/*
 * Author: RainAir
 * Time: 2019-08-16 20:08:16
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
const int MAXN = 1e5 + 5;

int f1[MAXN][2],f2[MAXN][2],F[MAXN],G[MAXN],nxt[MAXN];
// f1 xuan f2 buxuan
bool vis[MAXN];
int n,du[MAXN];

inline int update(int fa,int v,int f[][2],bool flag){
    while("NOIP2019 ++score"){
        int to = nxt[v];
        vis[v] = vis[to] = true;
        if(to == fa) break;
        f[to][0] += std::max(f[v][0],f[v][1]);
        f[to][1] += std::max(f[v][0],f[v][1]+G[v]);
        v = to;
    }
    return std::max(f[v][0],f[v][1]+(flag?G[v]:0));
}

inline int dfs(int v){
    int to = nxt[v];
    f1[to][0] += f1[v][0];
    f1[to][1] += f1[v][0];
    int ans = update(v,to,f1,false);
    f2[to][0] += f2[v][1];
    f2[to][1] += f2[v][1]+G[v];
    ans = std::max(update(v,to,f2,true),ans);
    return ans;
}

inline void clear(){
    FOR(i,0,n) du[i] = 0,f1[i][1] = f1[i][0] = 0,vis[i] = 0,nxt[i] = 0;
}

inline void Solve(){
    FOR(i,1,n) scanf("%lld%lld%lld",F+i,G+i,nxt+i),du[nxt[i]]++,f1[i][1] = F[i],f1[i][0] = 0; // add(i,nxt[i])
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) q.push(i);
    while(!q.empty()){
        int v = q.front();q.pop();vis[v] = true;
        int to = nxt[v];
        f1[to][0] += std::max(f1[v][0],f1[v][1]);
        f1[to][1] += std::max(f1[v][0],f1[v][1]+G[v]);
        if(!--du[to]) q.push(to);
    }
    memcpy(f2,f1,sizeof(f1));
    int ans = 0;
    FOR(i,1,n){
        if(!vis[i]) ans += dfs(i);
    }
    printf("%lld\n",ans);
    clear();
}

signed main(){
    while(~scanf("%lld",&n)) Solve();
    return 0;
}

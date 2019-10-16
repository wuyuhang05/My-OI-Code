/*
 * Author: RainAir
 * Time: 2019-10-11 15:46:44
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
int n,m;

std::vector<int> G[MAXN],ans;

int dfn[MAXN],low[MAXN];
bool cut[MAXN];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    int deg = 0;
    for(auto x:G[v]){
        if(!dfn[x]){
            deg++;
            dfs(x,v);low[v] = std::min(low[v],low[x]);
            if(low[x] >= dfn[v]) cut[v] = true;
        }
        else low[v] = std::min(low[v],dfn[x]);
    }
    if(!fa && deg == 1) cut[v] = 0;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int v,u;scanf("%d%d",&v,&u);
        G[v].pb(u);G[u].pb(v);
    }
    dfs(1);
    FOR(i,1,n){
        if(cut[i]) continue;
        if(G[i].size() == m-(n-2)) ans.pb(i);
    }
    printf("%lu\n",ans.size());
    for(auto x:ans) printf("%d ",x);puts("");
    return 0;
}

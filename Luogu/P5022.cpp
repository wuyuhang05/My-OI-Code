/*
 * Author: RainAir
 * Time: 2019-11-07 20:38:54
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

const int MAXN = 5000+5;

std::vector<int> G[MAXN],ans,tans;
int n,m;
int nowu,nowv;
P edge[MAXN];

inline bool chk(){
    if(tans.size() != n) return false;
    if(ans.empty()) return true;
    FOR(i,0,n-1){
        if(ans[i] < tans[i]) return false;
        if(ans[i] > tans[i]) return true;
    }
    return false;
}

bool vis[MAXN];

inline void dfs(int v,int fa=0){
    tans.pb(v);vis[v] = true;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if((x == nowu && v == nowv) || (x == nowv && v == nowu)) continue;
        if(x == fa) continue;
        if(vis[x]) continue;
        dfs(x,v);
    }
}

int main(){
    srand(20050117);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
        edge[i] = MP(u,v);
    }
    nowu = nowv = -1;
    FOR(i,1,n) std::sort(all(G[i]));
    if(m == n-1){
        dfs(1);
        FOR(i,0,(int)tans.size()-1) printf("%d ",tans[i]);
        puts("");
        return 0;
    }
    std::random_shuffle(edge+1,edge+m+1);
    FOR(i,1,m){
        tans.clear();FOR(i,1,n) vis[i] = 0;
        nowu = edge[i].fi,nowv = edge[i].se;
        dfs(1);
        if(chk()) ans = tans;
    }
    FOR(i,0,(int)ans.size()-1) printf("%d ",ans[i]);
    puts("");
    return 0;
}

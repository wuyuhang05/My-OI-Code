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

const int MAXN = 2e5 + 5;
std::vector<int> G[MAXN];
LL sz[MAXN],ans,now;
int n;

inline void dfs1(int v){
    sz[v] = 1;
    for(auto x:G[v]){
        if(sz[x]) continue;
        dfs1(x);sz[v] += sz[x];
    }
    ans += sz[v];now += sz[v];
}

inline void dfs2(int v,int fa,LL now){
    ans = std::max(ans,now);
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs2(x,v,now+n-2ll*sz[x]);
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dfs1(1);dfs2(1,0,ans);
    printf("%lld\n",ans);
    return 0;
}

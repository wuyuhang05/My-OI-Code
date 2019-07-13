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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair<int,int>
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
std::vector<int> ans;
std::vector<P> G[MAXN];
int n,m,cnt;
bool vis[MAXN];

inline void dfs(int v){
    FOR(i,0,(int)G[v].size()-1){
        P x = G[v][i];
        if(!vis[x.se]){
            vis[x.se] = true;
            dfs(x.fi);
        }
    }
    ans.pb(v);
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(MP(v,++cnt));G[v].pb(MP(u,++cnt));
    }
    dfs(1);
    FOR(i,0,(int)ans.size()-1) printf("%d\n",ans[i]);
    return 0;
}

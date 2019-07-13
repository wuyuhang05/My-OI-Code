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

const int MAXN = 2000+5;
const int MAXM = 20000+5;

std::vector<int> G[MAXN],T[MAXN];
std::bitset<MAXN> to[MAXM];
bool vis[MAXN];
int n,m,ans;

inline void dfs(int v,int fa=-1){
    vis[v] = true;
    to[v].reset();
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(vis[x]) to[v].set(x);
    }
    FOR(i,0,(int)T[v].size()-1){
        int x = T[v][i];
        if(x == fa) continue;
        dfs(x,v);
    }
    if(fa == -1) return;
    if(to[v][fa]) ans++;
    else to[fa] |= to[v];
}

inline void clear(){
    FOR(i,1,n) G[i].clear(),T[i].clear(),vis[i] = false;ans = 0;
}

int main(){
    while(~scanf("%d%d",&n,&m) && (n + m)){
        FOR(i,1,n-1){
            int u,v;scanf("%d%d",&u,&v);
            T[u].pb(v);T[v].pb(u);
        }
        FOR(i,n,m){
            int u,v;scanf("%d%d",&u,&v);
            G[u].pb(v);G[v].pb(u);
        }
        dfs(1);printf("%d\n",ans);
        clear();
    }
    return 0;
}

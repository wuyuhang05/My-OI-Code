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

const int MAXN = 2e5 + 5;
int n,m;
std::vector<P> G[MAXN];

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}
bool vis[MAXN],ins[MAXN];
int dis[MAXN];
inline int dfs(int v){
    vis[v] = ins[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(!vis[e[i].to]){
            dis[e[i].to] = dis[v] + e[i].w;
            int res = dfs(e[i].to);
            if(res != -1) return res;
        }
        else if(ins[e[i].to]) return dis[v]-dis[e[i].to]+e[i].w;
    }
    ins[v] = 0;
    return -1;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        FOR(j,1,n){
            int x;scanf("%d",&x);
            if(x) G[j].pb(MP(x,i));
        }
    }
    FOR(i,1,n){
        std::sort(all(G[i]));std::reverse(all(G[i]));
        FOR(j,1,(int)G[i].size()-1){
            if(G[i][j].fi == 0) break;
            add(G[i][j-1].se,G[i][j].se,G[i][j-1].fi-G[i][j].fi);
        }
    }
    int ans = -1;
    FOR(i,1,m){
        if(!vis[i]){
            ans = dfs(i);
            if(ans != -1){printf("%d\n",ans);return 0;}
        }
    }
    printf("%d\n",-1);
    return 0;
}

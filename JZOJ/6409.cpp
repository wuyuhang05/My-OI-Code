/*
 * Author: RainAir
 * Time: 2019-11-06 14:21:52
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

const int MAXN = 1e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt = 1;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int bel[MAXN];
int low[MAXN],dfn[MAXN];
int stk[MAXN],tp,n,m;
std::vector<int> edge;
bool can[MAXN],vis[MAXN];

inline void up(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
//                DEBUG(v);DEBUG(e[i].to);
//DEBUG(can[e[i].to]);
        if(!can[e[i].to]) continue;
        int id = i>>1;
        if(vis[id]) continue;
        vis[id] = true;
        edge.pb(id);
        up(e[i].to,fa);
    }
}

int ans = 0;

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    stk[++tp] = v;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        if(!dfn[e[i].to]){
            dfs(e[i].to,v);
            low[v] = std::min(low[v],low[e[i].to]);
  //          DEBUG(low[e[i].to]);DEBUG(dfn[v]);
    //        DEBUG(v);DEBUG(e[i].to);
            if(low[e[i].to] >= dfn[v]){
                int t = -1;int cnt = 0;
                do{
                    t = stk[tp--];
                    can[t] = true;++cnt;
                }while(t != e[i].to);
             //   DEBUG(v);
      //          FOR(i,1,n) DEBUG(can[i]);
                up(t);edge.pb(e[i]/2);
                if(edge.size() == cnt+1){
                    FOR(i,0,(int)edge.size()-1) ans ^= edge[i],vis[edge[i]] = false;
                }
                edge.clear();
            }
        }
        else{
            low[v] = std::min(low[v],dfn[e[i].to]);
        }
    }
//    DEBUG(v);DEBUG(low[v]);DEBUG(dfn[v]);
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    dfs(1);
    printf("%d\n",ans);
    return 0;
}

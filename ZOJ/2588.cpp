/*
 * Author: RainAir
 * Time: 2019-08-23 08:00:43
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;

struct Edge{
    int to,nxt,id,tag;
}e[MAXN<<1];
int n,m;
int head[MAXN],low[MAXN],dfn[MAXN],cnt;

inline void add(int u,int v,int id){
    bool flag = false;
    for(int i = head[u];i;i = e[i].nxt) if(e[i].to == v) {e[i].tag++;flag = true;break;}
    for(int i = head[v];i;i = e[i].nxt) if(e[i].to == u) {e[i].tag++;flag = true;break;}
    if(flag) return;
    e[++cnt] = (Edge){v,head[u],id,1};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],id,1};head[v] = cnt;
}

std::vector<int> ans;

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        else if(!dfn[e[i].to]){
            dfs(e[i].to,v);
            low[v] = std::min(low[v],low[e[i].to]);
            if(low[e[i].to] > dfn[v] && e[i].tag == 1){
                ans.pb(e[i].id);
            }
        }
        else{
            low[v] = std::min(low[v],dfn[e[i].to]);
        }
    }
}

inline void clear(){
    ans.clear();CLR(head,0);CLR(dfn,0);CLR(low,0);cnt = 0;
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v,i);
    }
    dfs(1);
    printf("%d\n",(int)ans.size());
    for(auto x:ans) printf("%d ",x);
    if(ans.size() > 0) puts("");
    clear();
}

int main(){
    int T;scanf("%d",&T);
    FOR(i,1,T){
        Solve();
        if(i != T) puts("");
    }
    return 0;
}

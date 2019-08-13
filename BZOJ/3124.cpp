/*
 * Author: RainAir
 * Time: 2019-08-09 21:38:05
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

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],dep[MAXN],dis[MAXN],pre[MAXN],cnt;
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

std::vector<int> l;

inline int bfs(int S){
    std::queue<int> q;q.push(S);
    FOR(i,1,n) dis[i] = LLONG_MAX,pre[i] = 0;
    dis[S] = 0;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] != LLONG_MAX) continue;
            dis[e[i].to] = dis[v] + e[i].w;pre[e[i].to] = v;
            q.push(e[i].to);
        }
    }
    int mx = 0,res = 0;
    FOR(i,1,n){
        if(mx < dis[i]) mx = dis[i],res = i;
    }
    if(S != 1){
        int v = res;
        while(v){//DEBUG(v);
            l.pb(v);
            v = pre[v];
        }
        FOR(i,0,(int)l.size()-1) vis[l[i]] = true;
    }
    return res;
}

int mx = 0;
inline void dfs(int v,int sm=0,int fa=0){
    mx = std::max(mx,sm);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || vis[e[i].to]) continue;
        dfs(e[i].to,sm+e[i].w,v);
    }
}

inline int calc(std::vector<int> v){
    int res = 0,d = std::abs(dis[v[0]]-dis[v[1]]);
    FOR(i,1,(int)v.size()-1){
        mx = 0;dfs(v[i]);
        if(mx == d) res = i;
        if(i != v.size()-1)d += std::abs(dis[v[i]]-dis[v[i+1]]);
    }
    return res;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n-1){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    int ans1 = dis[bfs(bfs(1))];printf("%lld\n",ans1);
    //for(auto x:l) DEBUG(x);
    int l = calc(::l);//DEBUG(l);
    std::reverse(all(::l));
    int r = calc(::l);//DEBUG(r);
    r = ::l.size()-r-1;
    printf("%lld\n",r-l);
    return 0;
}

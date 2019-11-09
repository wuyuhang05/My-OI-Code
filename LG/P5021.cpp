/*
 * Author: RainAir
 * Time: 2019-11-07 21:50:18
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

const int MAXN = 5e4 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,m;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int f[MAXN],g[MAXN],k;
std::multiset<int> S;

inline void dfs(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt) if(e[i].to != fa) dfs(e[i].to,v);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        S.insert(g[e[i].to]+e[i].w);
    }
    while(!S.empty() && *S.rbegin() >= k){
        f[v]++;S.erase(S.find(*S.rbegin()));
    }
    int ttt = v;
    while(!S.empty()){
        int v = *S.begin();S.erase(S.begin());
        std::multiset<int>::iterator t = S.lower_bound(k-v);
        if(t == S.end()){
            g[ttt] = v;
            continue;
        }
        S.erase(t);
        f[ttt]++;
    }
    S.clear();
}

inline bool chk(int k){
    ::k = k;
    dfs(1);
    int ans = 0;
    FOR(i,1,n) ans += f[i];
    FOR(i,1,n) f[i] = g[i] = 0;
    return ans >= m;
}

int dis[MAXN];
bool vis[MAXN];
inline int bfs(int v){
    FOR(i,1,n) dis[i] = 1e9,vis[i] = 0;
    std::queue<int> q;q.push(v);dis[v] = 0;
    while(!q.empty()){
        int v = q.front();q.pop();
        vis[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(!vis[e[i].to]){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(e[i].to);
            }
        }
    }
    int mx = 0;
    FOR(i,1,n) if(dis[i] > dis[mx]) mx = i;
    return mx;
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    int l = 0,r = dis[bfs(bfs(1))],ans = 0;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    printf("%d\n",ans);
    return 0;
}

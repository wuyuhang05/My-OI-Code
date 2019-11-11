/*
 * Time: 2019-11-11 21:20:39
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

const int MAXN = 1e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt,MX,n,m;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int dis[MAXN][105];
bool inq[MAXN][105];

inline void spfa(){
    FOR(i,1,n) FOR(j,0,MX) dis[i][j] = 1e9;
    dis[1][0] = 0;
    std::queue<P> q;
    q.push(MP(1,0));inq[1][0] = true;
    while(!q.empty()){
        int v = q.front().fi,s = q.front().se;q.pop();
        inq[v][s] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            int t = (s+e[i].w)%MX;
            if(dis[e[i].to][t] > dis[v][s] + e[i].w){
                dis[e[i].to][t] = dis[v][s] + e[i].w;
                if(!inq[e[i].to][t]) q.push(MP(e[i].to,t)),inq[e[i].to][t] = 1;
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    MX = 1e9;
    for(int i = head[1];i;i = e[i].nxt) MX = std::min(MX,e[i].w*2);
    spfa();
    int q;scanf("%d",&q);
    while(q--){
        int x;scanf("%d",&x);
        puts(dis[n][x%MX] <= x ? "AWaDa!" : "AKTang!");
    }
    return 0;
}

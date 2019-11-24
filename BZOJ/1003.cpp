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
 
const int MAXN = 200+5;
 
struct Edge{
    int to,w,nxt;
}e[(MAXN*MAXN)<<1];
 
int head[MAXN],cnt;
 
inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}
 
LL dis[MAXN];
bool used[MAXN],del[MAXN];
int N,M,K,E,D;
 
inline void dij(){
    FOR(i,1,M) dis[i] = 1e18;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;q.push(MP(dis[1] = 0,1));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        if(del[v]) continue;
        used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(del[e[i].to]) continue;
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
    FOR(i,1,M) used[i] = del[i] = 0;
}
 
bool tag[MAXN][MAXN];
LL f[MAXN],g[MAXN][MAXN];
 
int main(){
    scanf("%d%d%d%d",&N,&M,&K,&E);
    FOR(i,1,E){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    scanf("%d",&D);
    FOR(i,1,D){
        int x,l,r;scanf("%d%d%d",&x,&l,&r);
        FOR(j,l,r) tag[x][j] = 1;
    }
    FOR(l,1,N){
        FOR(r,l,N){
            FOR(i,1,M){
                FOR(j,l,r) del[i] |= tag[i][j];
            }
            dij();
            if(dis[M] == 1e18) g[l][r] = -1;
            else g[l][r] = 1ll*(r-l+1)*dis[M];
        }
    }
    f[0] = -K;
    FOR(i,1,N){
        f[i] = 1e18;
        FOR(j,0,i-1){
            if(g[j+1][i] != -1)
                f[i] = std::min(f[i],f[j]+g[j+1][i]+K);
        }
    }
    printf("%lld\n",f[N]);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-07 18:39:13
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
#define int LL
const int MAXN = 1e5 + 5;
const int MAXM = 5e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXM<<1];
int head[MAXN],bk[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int dis[MAXN];
bool used[MAXN];
std::vector<int> inte;
int S,T,n,m,k;

inline int dij(int base,int d){
    int prec = cnt;
    FOR(i,1,T) head[i] = bk[i];
    for(auto x:inte){
        if(((1<<base)&x) == (1<<base)*d) add(S,x,0);//,DEBUG(x);
        else add(x,T,0);
    }
    FOR(i,1,T) used[i] = 0,dis[i] = 1e18;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    q.push(MP(dis[S] = 0,S));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
    cnt = prec;
    return dis[T];
}

inline void clear(){
    inte.clear();cnt = 0;
    FOR(i,1,n+2) head[i] = bk[i] = 0;
}

inline void Solve(){
    scanf("%lld%lld%lld",&n,&m,&k);
    S = n+1,T = n+2;
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    FOR(i,1,k){
        int x;scanf("%lld",&x);
        inte.pb(x);
    }
    int ans = 1e18;
    FOR(i,1,n) bk[i] = head[i];
//    DEBUG(dij(3,1));
    FOR(i,0,18) ans = std::min(ans,std::min(dij(i,0),dij(i,1)));
    printf("%lld\n",ans);
    clear();//exit(0);
}

signed main(){
    freopen("2.in","r",stdin);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

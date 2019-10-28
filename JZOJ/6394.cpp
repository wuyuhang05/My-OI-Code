/*
 * Author: RainAir
 * Time: 2019-10-28 14:50:32
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
#define P std::pair<LL,int>
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
const int MAXK = 20 + 1;
const int ha = 998244353;

struct Edge{
    int to,w,nxt;
}e[MAXN<<2];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

LL dis[MAXK][MAXN];
int fire[MAXN];
int n,m,k;
bool used[MAXN];

inline void dij(int k){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,1,n) dis[k][i] = 1e18,used[i] = 0;
    dis[k][fire[k]] = 0;q.push(MP(0,fire[k]));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[k][e[i].to] > dis[k][v] + e[i].w){
                dis[k][e[i].to] = dis[k][v] + e[i].w;
                q.push(MP(dis[k][e[i].to],e[i].to));
            }
        }
    }
}

int a[MAXN];
bool f[(1<<MAXK)+3];

inline void FWT(){
    FOR(i,0,k-1){
        FOR(S,0,(1<<k)-1){
            if((1<<i)&S) f[S^(1<<i)] |= f[S];
        }
    }
}

signed main(){
    freopen("flame.in","r",stdin);
    freopen("flame.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&k);
    FOR(i,1,k) scanf("%lld",fire+i);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    FOR(i,1,k) dij(i);
    int mx = 0;
    FOR(i,1,n){
        int mn = 1e18;
        FOR(j,1,k) mn = std::min(mn,dis[j][i]);
        mx = std::max(mx,mn);
    }
    FOR(i,1,n){
        FOR(j,0,k-1){
            if(dis[j+1][i] <= mx) a[i] |= (1<<j);
        }
        a[i] ^= ((1<<k)-1);
    }
    //FOR(i,1,n) DEBUG(a[i]);
    FOR(i,1,n) f[a[i]] = 1;
    FWT();
    int ans = 0;
    FOR(i,0,(1<<k)-1) if(!f[i]) ans++;
    printf("%lld\n",1ll*ans*qpow((1<<k))%ha);
    return 0;
}

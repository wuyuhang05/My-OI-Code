/*
 * Author: RainAir
 * Time: 2019-11-05 19:38:55
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

const int MAXN = 5000+5;
const int ha = 998244353;
int f[MAXN][MAXN];

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int n,k;
int sz[MAXN],fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int suf[MAXN],tmp[MAXN];

inline void merge(int x,int y){
//    printf("%d %d %d %d\n",x,y,sz[x],sz[y]);
    suf[sz[y]+1] = fac[sz[y]];
    ROF(i,sz[y],0) suf[i] = (suf[i+1]+f[y][i]) % ha;
    FOR(i,0,sz[x]+sz[y]) tmp[i] = 0;
    FOR(p,1,sz[x]){
        FOR(k,p,p+sz[y]){
            (tmp[k] += 1ll*f[x][p]*suf[k-p+1]%ha*C(k-1,p-1)%ha*C(sz[x]+sz[y]-k,sz[x]-p)%ha) %= ha;
        }
    }
    std::swap(x,y);
    suf[sz[y]+1] = fac[sz[y]];
    ROF(i,sz[y],0) suf[i] = (suf[i+1]+f[y][i]) % ha;
    FOR(p,1,sz[x]){
        FOR(k,p,p+sz[y]){
            (tmp[k] += 1ll*f[x][p]*suf[k-p+1]%ha*C(k-1,p-1)%ha*C(sz[x]+sz[y]-k,sz[x]-p)%ha) %= ha;
        }
    }
    std::swap(x,y);
    FOR(i,0,sz[x]+sz[y]) f[x][i] = tmp[i];
}

inline void dfs(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        merge(v,e[i].to);
        sz[v] += sz[e[i].to];
    }
    sz[v]++;
    suf[sz[v]+1] = 0;
    ROF(i,sz[v],1) suf[i] = (suf[i+1]+f[v][i]) % ha;
    ROF(i,sz[v],1){
        f[v][i] = (1ll*f[v][i-1]*(i-1)%ha+1ll*k*suf[i]%ha+1ll*k*fac[sz[v]-1]%ha)%ha;
    }
}

int main(){
    freopen("a.in","r",stdin);
    //freopen("random.out","w",stdout);
    scanf("%d%d",&n,&k);--k;
    prework();
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);//add(v,u);
    }
    dfs(1);
    int ans = fac[n];
    FOR(i,1,n) (ans += f[1][i]) %= ha;
    printf("%d\n",ans);
    return 0;
}

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

const int MAXN = 2500+5;
const int ha = 1e9 + 7;

int fac[MAXN],inv[MAXN];

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
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int n,m;

struct Edge{
    int u,v,w;
}edge[MAXN];
std::vector<P> G[MAXN];
int sz[MAXN];
int x[MAXN],y[MAXN];

inline void dfs(int v,int fa=0){
    sz[v] = 1;
    for(auto x:G[v]){
        if(x.fi == fa) continue;
        dfs(x.fi,v);
        sz[v] += sz[x.fi];
        ::x[x.se] = sz[x.fi];::y[x.se] = n-sz[x.fi];
    }
}

int f[MAXN],f1[MAXN],f2[MAXN];

int main(){
    scanf("%d%d",&n,&m);prework();
    FOR(i,1,n-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);edge[i] = (Edge){u,v,w};
        G[u].pb(MP(v,i));G[v].pb(MP(u,i));
    }
    dfs(1);
    int ans = 0;
    FOR(e,1,n-1){
        int w = edge[e].w,x = ::x[e],y = ::y[e];
        FOR(j,0,m){
            f[j] = 1ll*C(m,j)*qpow(x,j)%ha*qpow(y,m-j)%ha;
            f1[j] = 1ll*f[j]*j%ha;f2[j] = 1ll*f[j]*(m-j)%ha;
        }
        FOR(j,1,m){
            (f[j] += f[j-1]) %= ha;
            (f1[j] += f1[j-1]) %= ha;
            (f2[j] += f2[j-1]) %= ha;
        }
        int now = 0;
        FOR(i,0,m){
            int t = 0;
            (t += 1ll*f[m-i]*i%ha) %= ha;
            (t += (f2[m]+ha-f2[m-i])%ha) %= ha;
            (t += f1[m-i]) %= ha;
            (t += 1ll*(f[m]+ha-f[m-i])%ha*(m-i)%ha) %= ha;
            t = 1ll*t*C(m,i)%ha*qpow(x,i)%ha*qpow(y,m-i)%ha;
            (now += t) %= ha;
        }
        now = 1ll*now*w%ha;
        (ans += now) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}

#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 300000+5;
const int MAXK = 50+5;
const int ha = 998244353;

LL dep[MAXN][MAXK],sum[MAXN][MAXK];

std::vector<int> G[MAXN];
int f[MAXN][30];
int n,m;
float logn;

void dfs(int v){
    FOR(i,1,logn){
        if((1<<i) >= dep[v][1]) break;
        f[v][i] = f[f[v][i-1]][i-1];
    }
    dep[v][0] = 1;
    FOR(i,2,MAXK-1) dep[v][i] = 1ll*dep[v][i-1]*dep[v][1]%ha;
    FOR(i,0,MAXK-1) sum[v][i] = (sum[v][i] + dep[v][i])%ha;
    for(auto x:G[v]){
        if(x == f[v][0]) continue;
        f[x][0] = v;dep[x][1] = dep[v][1] + 1;
        FOR(i,0,MAXK-1) sum[x][i] = sum[v][i];
        dfs(x);
    }
}

inline int lca(int x,int y){
    if(dep[x][1] != dep[y][1]){
        if(dep[x][1] < dep[y][1]) std::swap(x,y);
        int d = dep[x][1] - dep[y][1];
        FOR(i,0,logn){
            if((1<<i)&d) x = f[x][i];
        }
    }
    if(x == y) return x;
    ROF(i,logn,0){
        if(f[x][i] == f[y][i]) continue;
        x = f[x][i],y = f[y][i];
    }
    return f[x][0];
}

int main(){
    scanf("%d",&n);logn = log2(n);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G[u].pb(v);G[v].pb(u);
    }
    dfs(1);
    scanf("%d",&m);
    while(m--){
        int x,y,k;scanf("%d%d%d",&x,&y,&k);
        int l = lca(x,y);
        LL ans = (sum[x][k] + sum[y][k] - 2ll*sum[l][k] + dep[l][k]);
        while(ans < 0) ans += ha;ans %= ha;
        printf("%lld\n",ans);
    }
    return 0;
}

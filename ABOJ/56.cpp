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
#define Re register
#define LL long long
#define pb push_back
#define db long double
#define MP std::make_pair
#define P std::pair<int,int>
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;

std::vector<P> G[MAXN];

inline void add(int u,int v,int w){
    G[u].pb(MP(v,w));G[v].pb(MP(u,w));
}

db f[MAXN][5005];
int n,m,k,val[MAXN],c[MAXN],h1[MAXN],h2[MAXN];

inline db dfs(int v,int limit){
    if(f[v][limit] != -1) return f[v][limit];
    db cnt = 0;
    f[v][limit] = val[v];
    for(auto i : G[v]) if(c[i.fi] + i.se <= limit) ++cnt;
    if(cnt == 0) return f[v][limit];
    for(auto i : G[v]){
        if(c[i.fi] + i.se > limit) continue;
        f[v][limit] += dfs(i.fi,limit-c[i.fi]-i.se)/cnt;
    }
    return f[v][limit];
}

inline void clr(){
    FOR(i,0,MAXN-20) FOR(j,0,550) f[i][j] = -1;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,n) scanf("%d%d%d",c+i,h1+i,h2+i);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    memcpy(val,h1,sizeof(h1));clr();
    db cnt = 0;FOR(i,1,n) if(c[i] <= k) ++cnt;
    db ans = 0.0;
    FOR(i,1,n) ans += dfs(i,k-c[i])/cnt;
    printf("%.5f ",(double)ans);
    memcpy(val,h2,sizeof(h2));clr();ans = 0.0;
    FOR(i,1,n) ans += (dfs(i,k-c[i])/cnt);
    printf("%.5f",(double)ans);
    return 0;
}

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

const int MAXN = 800+5;
std::vector<int> G[MAXN];
int sz[MAXN],dep[MAXN],dfn[MAXN],nfd[MAXN];

inline void dfs(int v,int fa=0){
    static int ts=0;dfn[v] = ++ts;nfd[ts] = v;
    dep[v] = dep[fa]+1;sz[v] = 1;
    for(auto x:G[v]){
        if(x == fa) continue;
        dfs(x,v);sz[v] += sz[x];
    }
}

bool f[MAXN][524288+5];
int n;
inline bool chk(int k){
    bool res = 0;
    FOR(i,0,n) FOR(S,0,(1<<k)-1) f[i][S] = 0;
    f[1][0] = 1;
    FOR(i,1,n){
        if(dep[nfd[i]] > k) continue;
        FOR(S,0,(1<<k)-1){
            if(!f[i][S]) continue;
            f[i+1][S] |= f[i][S];
            if(i != 1)
                if(!((S>>(dep[nfd[i]]-1))&1)){
                    f[i+sz[nfd[i]]][S|(1<<(dep[nfd[i]]-1))] |= f[i][S];
                }
        }
    }
    FOR(S,0,(1<<k)-1) res |= f[n+1][S];
    return res;
}
int du[MAXN];
int main(){
    dep[0] = -1;
    scanf("%d",&n);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);G[u].pb(v);G[v].pb(u);
        du[u]++;du[v]++;
    }
    int _n = n;
    FOR(i,1,_n) if(du[i] == 1) ++n,G[i].pb(n),G[n].pb(i);
    dfs(1);
    FOR(i,0,n){
        if(chk(i)){
            printf("%d\n",i);return 0;
        }
    }
    return 0;
}

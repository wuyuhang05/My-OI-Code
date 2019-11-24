/*
 * Time: 2019-11-13 21:19:20
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

const int MAXN = 10000+5;
const int MAXM = 100+5;
int f[MAXN][MAXM];
int n,k;
int up[MAXN],down[MAXN],sz[MAXN];

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

inline void dfs1(int v,int fa=0){
    sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs1(e[i].to,v);sz[v] += sz[e[i].to];
        down[v] += down[e[i].to]+sz[e[i].to];
    }
}

inline void dfs2(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        up[e[i].to] = up[v]+n+down[v]-down[e[i].to]-2*sz[e[i].to];
        dfs2(e[i].to,v);
    }
}

int ans=1e9;

inline void dfs3(int v,int fa=0){
    f[v][0] = 1e9;FOR(i,2,k+1) f[v][i] = 1e9;
    f[v][1] = down[v];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs3(e[i].to,v);
        FOR(j,1,k){
            ans = std::min(ans,f[v][j]+f[e[i].to][k-j+1]-down[e[i].to]-sz[e[i].to]+up[v]);
        }
        FOR(j,1,k+1){
            f[v][j] = std::min(f[v][j],f[e[i].to][j-1]+down[v]-down[e[i].to]-sz[e[i].to]);
        }
    }
    ans = std::min(ans,up[v]+f[v][k+1]);
}

inline void clear(){
    CLR(head,0);cnt = 0;
    CLR(up,0);CLR(down,0);CLR(sz,0);CLR(f,0);
    ans = 1e9;
}

inline void Solve(){
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        ++u;++v;
        add(u,v);
    }
    dfs1(1);dfs2(1);dfs3(1);
    printf("%d\n",ans);
    clear();
}

int main(){
    while(scanf("%d%d",&n,&k) == 2 && (n+k)) Solve();
    return 0;
}

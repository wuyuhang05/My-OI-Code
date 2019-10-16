/*
 * Author: RainAir
 * Time: 2019-09-13 20:41:06
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

const int ha = 998244353;
const int MAXN = 10000+5;
const int MAXK = 500+5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN][MAXK],n,k;

inline void upd(int &x,int y){
    x += y;while(x >= ha) x -= ha;
    while(x < 0) x += ha;
}

inline void update(int x,int y){ // y mergeto x
    static int f[MAXN],g[MAXN];
    FOR(i,0,k) f[i] = ::f[x][i],g[i] = ::f[y][i];
    f[k+1] = g[k+1] = 0;
    ROF(i,k,0) upd(f[i],f[i+1]),upd(g[i],g[i+1]);
    FOR(i,0,k){
        int sm = 0;
        upd(sm,1ll*::f[x][i]*g[std::max(i,k-i)]%ha);
        upd(sm,1ll*::f[y][i]*f[std::max(i,k-i)]%ha);
        // 因为 f[x][i] 表示的是距离最近选择的点距离为 i，所以需要保证另一个数的距离至少是 i
        if(i >= k-i) upd(sm,ha-1ll*::f[x][i]*::f[y][i]%ha); // 重复计算了
        ::f[x][i] = sm;
    }
}

inline void dfs(int v,int fa=0){
    f[v][0] = f[v][k] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        upd(f[e[i].to][k],f[e[i].to][k-1]);
        ROF(x,k-1,1) f[e[i].to][x] = f[e[i].to][x-1];
        f[e[i].to][0] = 0;
        update(v,e[i].to);
    }
}

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs(1);int ans = 0;
    FOR(i,0,k) upd(ans,f[1][i]);
    printf("%d\n",ans);
    return 0;
}

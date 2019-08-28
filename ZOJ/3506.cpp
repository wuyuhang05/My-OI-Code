/*
 * Author: RainAir
 * Time: 2019-08-16 19:04:37
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
const int MAXK = 20+5;
int f[MAXN][MAXK][2];
int n,k;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],sz[MAXN],val[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}
// 0最小 1 最大
inline void dfs(int v,int fa=0){
    FOR(i,0,k) f[v][i][0] = 1e9,f[v][i][1] = -1e9;
    f[v][0][0] = f[v][0][1] = 0;sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);//DEBUG(k);
        ROF(x,k,0){
            f[v][x][0] += f[e[i].to][0][0];
            f[v][x][1] += f[e[i].to][0][1];
            FOR(y,1,x){
                f[v][x][0] = std::min(f[v][x][0],f[v][x-y][0]+f[e[i].to][y][0]);
                f[v][x][1] = std::max(f[v][x][1],f[v][x-y][1]+f[e[i].to][y][1]);
            }
            FOR(y,0,std::min(sz[e[i].to],x)-1){
                f[v][x][0] = std::min(f[v][x][0],f[v][x-y-1][0]);
                f[v][x][1] = std::max(f[v][x][1],f[v][x-y-1][1]);
            }
        }
        sz[v] += sz[e[i].to];
    }
    FOR(i,0,k){
        f[v][i][0] += val[v];
        f[v][i][1] += val[v];
    }
}

inline void clear(){
    cnt = 0;
    FOR(i,0,n) head[i] = val[i] = 0;
    CLR(f,0);
}

inline void Solve(){
    FOR(i,1,n) scanf("%d",val+i);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    dfs(1);int ans1 = f[1][k][0],ans2 = f[1][k][1];
    FOR(i,2,n){
        for(int j = 1;j <= k && j <= n-sz[i];++j){
            ans1 = std::min(ans1,f[i][k-j][0]);
            ans2 = std::max(ans2,f[i][k-j][1]);
        }
    }
    printf("%d %d\n",ans1,ans2);
    clear();
}

int main(){
    while(~scanf("%d%d",&n,&k)) Solve();
    return 0;
}

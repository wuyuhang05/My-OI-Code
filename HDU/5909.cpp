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

const int MAXN = 2048+5;
const int ha = 1e9 + 7;
const int inv2 = 500000004;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,m;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN][MAXN];
int N;

inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;
                f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)*inv2%ha;
                f[i+mid+j] = 1ll*(x+ha-y)*inv2%ha;
            }
        }
    }
}

inline void dfs(int v,int fa=0){
    FWT(f[v]);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        FOR(j,0,N-1) f[v][j] = 1ll*f[v][j]*f[e[i].to][j]%ha;
    }
    iFWT(f[v]);
    (f[v][0] += 1) %= ha;
    FWT(f[v]);
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    CLR(head,0);cnt = 0;CLR(f,0);
    FOR(i,1,n){
        int x;scanf("%d",&x);f[i][x]++;
    }
    N = 1;while(N <= m) N <<= 1;
    // DEBUG(N);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);add(u,v);
    }
    dfs(1);
    FOR(i,1,n) iFWT(f[i]);
    FOR(i,0,n) (f[i][0] += ha-1)%=ha;
    FOR(i,0,m-1){
        int ans = 0;
        FOR(j,1,n) (ans += f[j][i]) %= ha;
        printf("%d%c",ans," \n"[i==m-1]);
    }
}

int main(){
    // DEBUG(1);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
/*
f[i][j][0/1]
i 子树 异或和是 j 是否选择根的代价和
每次合并处理包含根的所有连通块
f[i][x][1]+f[j][y][1] -> f'[i][x^y][1]
f[j][y][0/1] -> f[i][y][0]

f[i][j] i子树包含根权值为j的方案数
f[i][x]+f[j][y] -> f[i][x^y]
暴力做显然是 O(n|V|^2) 的
使用 FWT 优化到 O(n|V|log|V|)
*/
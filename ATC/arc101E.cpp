/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 16:11:09
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
const int ha = 1e9 + 7;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt,n;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN][MAXN],sz[MAXN],g[MAXN],tmp[MAXN];

inline void dfs(int v,int fa=0){
    sz[v] = 1;f[v][1] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        FOR(j,0,sz[v]+sz[e[i].to]) tmp[j] = 0;
        FOR(x,0,sz[v]){
            FOR(y,0,sz[e[i].to]){
                (tmp[x+y] += 1ll*f[v][x]*f[e[i].to][y]%ha)%=ha;
            }
        }
        sz[v] += sz[e[i].to];
        FOR(j,0,sz[v]) f[v][j] = tmp[j];
    }
    int sm = 0;
    FOR(i,1,sz[v]) (sm += ha-1ll*f[v][i]*g[i]%ha) %= ha;
    f[v][0] = sm;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    g[0] = 1;
    FOR(i,2,n) g[i] = 1ll*g[i-2]*(i-1)%ha;
    dfs(1);
    printf("%d\n",(ha-f[1][0])%ha);
    return 0;
}

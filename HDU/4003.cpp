/*
 * Author: RainAir
 * Time: 2019-08-15 20:18:12
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

const int MAXN = 1e5 + 5;
const int MAXK = 10+5;

int f[MAXN][MAXK];
int n,s,k;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],sz[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

void dfs(int v,int fa=0){
    sz[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        /*FOR(x,0,k) f[v][x] += 2*e[i].w+f[e[i].to][0];
        FOR(x,0,std::min(sz[v],k)){
            FOR(y,1,std::min(sz[e[i].to],k)){
                f[v][x+y] = std::min(f[v][x+y],f[v][x]+f[e[i].to][y]+y*e[i].w);
                if(x+y == k) {
                    DEBUG(v);
                    DEBUG(f[v][x]);
                    DEBUG(f[e[i].to][y]);
                    DEBUG(y*e[i].w);
                    DEBUG(f[v][x+y]);
                }
            }
        }*/
        ROF(x,k,0){
            f[v][x] += 2*e[i].w+f[e[i].to][0];
            FOR(y,1,x){
                f[v][x] = std::min(f[v][x],f[v][x-y]+f[e[i].to][y]+y*e[i].w);
            }
        }
        sz[v] += sz[e[i].to];
    }
}

inline void init(){
    cnt = 0;CLR(head,0);CLR(f,0);CLR(sz,0);
}

inline void Solve(){
    init();
    FOR(i,1,n-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    dfs(s);
    printf("%d\n",f[s][k]);
}

int main(){
    while(~scanf("%d%d%d",&n,&s,&k)) Solve();
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-11 16:42:23
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

const int MAXN = 600+5;
const int MAXM = 2e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXM<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int dis[MAXN],d[MAXN],n,m1,m2;
bool inq[MAXN];

inline bool spfa(){
    std::queue<int> q;
    int S = n+1;
    FOR(i,1,n) add(S,i,0);
    FOR(i,1,n) dis[i] = 1e9;dis[S] = 0;q.push(S);inq[S] = true;
    while(!q.empty()){
        int v = q.front();q.pop();inq[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                if(++d[e[i].to] > n) return true;
                if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = true;
            }
        }
    }
    int mx = 0;
    return false;
}

int dfn[MAXN],low[MAXN],col[MAXN];
int stk[MAXN],tp,tot;
bool ins[MAXN];

std::vector<int> blo[MAXN];

inline void dfs(int v,int fa=0){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    stk[++tp] = v;ins[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to,v);low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = stk[tp--];
            ins[t] = false;
            col[t] = tot;
            blo[tot].pb(t);
        }while(t != v);
    }
}

int f[MAXN][MAXN];
int S[MAXN];

inline int Floyd(int id){
    int n = blo[id].size();
    FOR(i,1,n) FOR(j,1,n) f[i][j] = 1e9*(i!=j);
    FOR(i,0,n-1) S[blo[id][i]] = i+1;
    FOR(i,0,n-1){
        int v = blo[id][i];
        for(int i = head[v];i;i = e[i].nxt){
            if(col[e[i].to] == col[v]) f[S[v]][S[e[i].to]] = std::min(f[S[v]][S[e[i].to]],e[i].w);
        }
    }
    FOR(k,1,n){
        FOR(i,1,n){
            FOR(j,1,n){
                f[i][j] = std::min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    int ans = 0;
    FOR(i,1,n) FOR(j,1,n) ans = std::max(ans,f[i][j]);
    return ans+1;
}

int main(){
 //   freopen("4.in","r",stdin);
    scanf("%d%d%d",&n,&m1,&m2);
    FOR(i,1,m1){
        int u,v;scanf("%d%d",&u,&v);
        add(v,u,-1);add(u,v,1);
    }
    FOR(i,1,m2){
        int u,v;scanf("%d%d",&u,&v);
        add(v,u,0);
    }
    if(spfa()){
        puts("NIE");
        return 0;
    }
    FOR(i,1,n) if(!dfn[i]) dfs(i); // 不连通！艹
    int ans = 0;
    FOR(i,1,tot) ans += Floyd(i);
    printf("%d\n",ans);
    return 0;
}

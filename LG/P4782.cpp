/*
 * Author: RainAir
 * Time: 2019-10-12 08:24:11
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

const int MAXN = 2e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<2];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m,N;
int dfn[MAXN],low[MAXN];
int st[MAXN],tp;
bool ins[MAXN];
int tot;
int col[MAXN];

std::vector<int> G[MAXN];

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;st[++tp] = v;ins[v] = true;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = st[tp--];
            col[t] = tot;ins[t] = false;
        }while(t != v);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,a,v,b;scanf("%d%d%d%d",&u,&a,&v,&b);
        add(u+n*(!a),v+n*b);add(v+n*(!b),u+n*a);
    }N = 2*n;
    FOR(i,1,N) if(!dfn[i]) dfs(i);
    FOR(v,1,N){
        for(int i = head[v];i;i = e[i].nxt){
            if(col[v] == col[e[i].to]) continue;
            G[col[v]].pb(col[e[i].to]);
        }
    }
    FOR(i,1,n) if(col[i] == col[n+i]){
        puts("IMPOSSIBLE");
        return 0;
    }
    puts("POSSIBLE");
    FOR(i,1,n) printf("%d ",col[n+i] < col[i]);
    puts("");
    return 0;
}

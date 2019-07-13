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

const int MAXN = 500000+5;

std::vector<int> G[MAXN],D[MAXN],ans;
int n,m,a[MAXN],dfn[MAXN],low[MAXN],tot;
int col[MAXN],sm[MAXN],S,PP;
bool vis[MAXN];std::stack<int> stk;

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    stk.push(v);vis[v] = true;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(!dfn[x]){
            dfs(x);
            low[v] = std::min(low[v],low[x]);
        }
        else if(vis[x]) low[v] = std::min(low[v],dfn[x]);
    }
    if(low[v] == dfn[v]){
        int r;++tot;
        do{
            r = stk.top();stk.pop();
            vis[r] = false;
            col[r] = tot;
            sm[tot] += a[r];
        }while(r != v);
    }
}

int dis[MAXN],du[MAXN];

inline void build(){
    FOR(u,1,n){
        if(!col[u]) continue;
        FOR(i,0,(int)G[u].size()-1){
            int v = G[u][i];
            if(col[v] == col[u]) continue;
            D[col[u]].pb(col[v]);
            du[col[v]]++;
        }
    }
}

bool used[MAXN];

inline void dp(){
    std::queue<int> q;q.push(col[S]);
    dis[col[S]] = sm[col[S]];
    while(!q.empty()){
        int v = q.front();q.pop();
        FOR(i,0,(int)D[v].size()-1){
            int x = D[v][i];
            dis[x] = std::max(dis[x],dis[v]+sm[x]);
            if(!--du[x]) q.push(x);
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);G[u].pb(v);
    }
    FOR(i,1,n) scanf("%d",a+i);scanf("%d%d",&S,&PP);
    FOR(i,1,PP){
        int x;scanf("%d",&x);ans.pb(x);
    }
    int res = 0;
    dfs(S);//FOR(i,1,n) DEBUG(col[i]);
    build();dp();
    FOR(i,0,PP-1){
        int x = ans[i];
        res = std::max(res,dis[col[x]]);
    }
    printf("%d\n",res);
    return 0;
}

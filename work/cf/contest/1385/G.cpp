/*
 * Author: RainAir
 * Time: 2019-10-12 08:44:47
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

const int MAXN = 1e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int cnt,head[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int n,m;
int dfn[MAXN],low[MAXN],col[MAXN];
int stk[MAXN],tp,tot;
bool ins[MAXN];

inline void dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;ins[v] = true;stk[++tp] = v;
    for(int i = head[v];i;i = e[i].nxt){
        if(!dfn[e[i].to]){
            dfs(e[i].to);low[v] = std::min(low[v],low[e[i].to]);
        }
        else if(ins[e[i].to]) low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = stk[tp--];
            ins[t] = false;col[t] = tot;
        }while(t != v);
    }
}

inline void clear(){
    FOR(i,0,2*n) col[i] = ins[i] = head[i] = dfn[i] = low[i] = 0;cnt = tot = 0;
}
int a[MAXN],b[MAXN];
std::vector<int> p[MAXN];
inline void Solve(){
    scanf("%d",&n);FOR(i,1,n) p[i].clear();
    FOR(i,1,n) scanf("%d",a+i),p[a[i]].pb(i);
    FOR(i,1,n) scanf("%d",b+i),p[b[i]].pb(-i);
    FOR(i,1,n){
        if(p[i].size() != 2){
            puts("-1");return;
        }
    }
    FOR(i,1,n){
        if(std::abs(p[i][0]) == std::abs(p[i][1])) continue;
        int x = std::abs(p[i][0]),y = std::abs(p[i][1]);
        if(p[i][0] > 0 && p[i][1] < 0){
            add(x,y);
            add(y+n,x+n);
            add(x+n,y+n);
            add(y,x);
        }
        else{
            add(x,y+n);add(y,x+n);
            add(x+n,y);add(y+n,x);
        }
    }
    FOR(i,1,2*n) if(!dfn[i]) dfs(i);
    FOR(i,1,n) if(col[i] == col[n+i]){
        puts("-1");
        clear();
        return;
    }
    int ans = 0;
    FOR(i,1,n) ans += (col[i]<col[n+i]);
    if(ans < n-ans){
        printf("%d\n",ans);
        FOR(i,1,n) if(col[i] < col[n+i]) printf("%d ",i);
        puts("");
    }
    else{
        printf("%d\n",n-ans);
        FOR(i,1,n) if(col[i] > col[n+i]) printf("%d ",i);
        puts("");
    }
    clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}


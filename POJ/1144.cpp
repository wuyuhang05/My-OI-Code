#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20000+5;
const int MAXM = 100000+5;

struct Edge{
    int to,next;
}e[MAXM<<1];
int head[MAXN],cnt,N,M;
int dfn[MAXN],low[MAXN],cut[MAXN];
std::stack<int> S;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

inline void dfs(int v,int fa){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    int tot = 0;
    for(int i = head[v];i;i = e[i].next){
        //DEBUG(i);DEBUG(e[i].to);
        if(!dfn[e[i].to]){
            dfs(e[i].to,fa);
            low[v] = std::min(low[v],low[e[i].to]);
            if(low[e[i].to] >= dfn[v] && v != fa) cut[v] = 1;
            if(v == fa) tot++;
        }
        low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(tot >= 2 && v == fa) cut[v] = 1;
}

inline void clear(){
    FOR(i,1,N) dfn[i] = low[i] = cut[i] = head[i] = 0;
    cnt = 0;while(!S.empty()) S.pop();
}

inline void Solve(){
    int u,v;
    while(~scanf("%d",&u) && u){
        while(getchar() != '\n'){
            scanf("%d",&v);
            add(u,v);add(v,u);
        }
    }
    FOR(i,1,N) if(!dfn[i]) dfs(i,i);
    int ans = 0;
    FOR(i,1,N) ans += cut[i];
    printf("%d\n",ans);
    //FOR(i,1,N) if(cut[i]) printf("%d ",i);
    //puts("");
    clear();
}

int main(){
    while(~scanf("%d",&N) && N) Solve();
    return 0;
}

/*
 * Time: 2019-12-02 20:03:19
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 4000+5;
const int MAXM = 100000+5;

struct Edge{
    int to,nxt,flow,cap;
}e[MAXM<<3];

int head[MAXN],cur[MAXN],dep[MAXN],cnt = 1;

inline void add(int u,int v,int cap){
    e[++cnt] = (Edge){v,head[u],0,cap};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

int S,T;
int n,m;

inline bool bfs(){
    std::queue<int> q;
    FOR(i,1,n) cur[i] = head[i],dep[i] = 0;
    dep[S] = 1;q.push(S);
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].flow < e[i].cap && !dep[e[i].to]){
                dep[e[i].to] = dep[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim=1e18){
    if(!lim) return 0;
    if(v == T) return lim;int flow;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].flow < e[i].cap && dep[e[i].to] == dep[v] + 1){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
                e[i].flow += flow;
                e[i^1].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int Dinic(){
    int res = 0,flow;
    while(bfs()){
        while((flow = dfs(S))) res += flow;
    }
    return res;
}

std::vector<int> G[MAXN];
int dfn[MAXN],low[MAXN];
int stk[MAXN],tp,tot;
bool ins[MAXN];
int col[MAXN];

inline void Dfs(int v){
    static int ts = 0;
    dfn[v] = low[v] = ++ts;
    ins[v] = true;stk[++tp] = v;
    FOR(i,0,(int)G[v].size()-1){
        int x = G[v][i];
        if(!dfn[x]){
            Dfs(x);
            low[v] = std::min(low[v],low[x]);
        }
        else if(ins[x]) low[v] = std::min(low[v],dfn[x]);
    }
//    if(v == 2) DEBUG(low[v]),DEBUG(dfn[v]);
//    if(v == 4) DEBUG(low[v]),DEBUG(dfn[v]);
    if(low[v] == dfn[v]){
        int t = -1;++tot;
        do{
            t = stk[tp--];
            ins[t] = false;
            col[t] = tot;
        }while(t != v);
    }
}

P edge[MAXM];
int ps[MAXM];

signed main(){
    // freopen("a.in","r",stdin);
    // freopen("a.out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&m,&S,&T);
    FOR(i,1,m){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);edge[i] = MP(u,v);ps[i] = cnt-1;
    }
    int res = Dinic();
    FOR(i,1,m) printf("flow:%lld cap:%lld\n",e[ps[i]].flow,e[ps[i]].cap);
    FOR(u,1,n){
        for(int i = head[u];i;i = e[i].nxt){
            if(e[i].flow < e[i].cap) G[u].pb(e[i].to);//,printf("%lld %lld\n",u,e[i].to);
        }
    }
    FOR(i,1,n) if(!dfn[i]) Dfs(i);
   // FOR(i,1,n) DEBUG(col[i]);
    FOR(i,1,m){
        if(e[ps[i]].flow == e[ps[i]].cap) assert(col[edge[i].fi] != col[edge[i].se]);
        if(e[ps[i]].flow < e[ps[i]].cap) puts("0 0");
        else printf("%c %c\n",'0'+(col[edge[i].fi] != col[edge[i].se]),'0'+(col[edge[i].fi]==col[S] && col[edge[i].se] == col[T]));
    }
    // DEBUG(res);
    return 0;
}
/*
6 6 1 6
1 2 4
2 3 2
2 4 2
3 5 2
4 5 2
5 6 4
 */

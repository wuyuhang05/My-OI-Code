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

const int MAXN = 2000+5;
const int MAXM = 100000+5;

int n,m;
struct Edge{
    int to,cap,flow,nxt;
}e[MAXM<<1];int cnt = 1;

int head[MAXN],dep[MAXN],cur[MAXN];

inline void add(int u,int v,int cap){
    e[++cnt] = (Edge){v,cap,0,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,0,head[v]};head[v] = cnt;
}

int S,T,N;
inline bool bfs(){
    FOR(i,0,N) cur[i] = head[i],dep[i] = 0;
    std::queue<int> q;q.push(S);dep[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].cap > e[i].flow && !dep[e[i].to]){
                dep[e[i].to] = dep[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim = INT_MAX){
    if(v == T) return lim;int flow;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(dep[e[i].to] == dep[v] + 1 && e[i].flow < e[i].cap){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap - e[i].flow)))){
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

inline void init(){
    cnt = 1;FOR(i,1,N) head[i] = 0;
}

inline void Solve(){init();
    scanf("%d%d",&n,&m);N = n+m+2;S = n+m+1,T = n+m+2;
    FOR(i,1,n){
        int cc;scanf("%d",&cc);
        FOR(j,1,cc){
            int x;scanf("%d",&x);
            add(i,n+x,INT_MAX);
        }
    }
    FOR(i,1,n) add(S,i,1);
    FOR(i,n+1,n+m) add(i,T,1);
    puts(Dinic() == n ? "YES" : "NO");
    init();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

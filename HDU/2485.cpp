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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200 + 5;
const int MAXM = 100000;

int n,m,k;
int G[MAXN][MAXN],f[MAXN][MAXN];
P edge[MAXM];

inline void Floyd(){
    FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) f[i][j] = std::min(f[i][j],f[i][k]+f[k][j]);
}

struct Edge{
    int to,flow,cap,nxt;
}e[MAXM<<2];
int cnt = 1;
int head[MAXN],cur[MAXN],dep[MAXN];

inline void add(int u,int v,int cap){
  //  printf("%d %d %d\n",u,v,cap);
    e[++cnt] = (Edge){v,0,cap,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,0,head[v]};head[v] = cnt;
}

int N;

inline bool bfs(){
    FOR(i,1,N) dep[i] = 0,cur[i] = head[i];
    std::queue<int> q;q.push(1);dep[1] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].flow < e[i].cap && !dep[e[i].to]){
                dep[e[i].to] = dep[v] + 1;
                if(e[i].to == N) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim=INT_MAX){
    if(v == N) return lim;int flow;//DEBUG(lim);DEBUG(v);
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].flow < e[i].cap && dep[e[i].to] == dep[v] + 1){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
                e[i].flow += flow;e[i^1].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int Dinic(){
    int ans = 0,flow;
    while(bfs()){
        while((flow = dfs(1))) ans += flow;//,DEBUG(flow);
    }
    return ans;
}

inline void clear(){
    cnt = 1;CLR(head,0);CLR(cur,0);CLR(dep,0);CLR(e,0);
}
int ttt;
inline void Solve(){ttt++;
    FOR(i,1,n) FOR(j,1,n) f[i][j] = 1e8,G[i][j] = 0;
    FOR(i,1,n) f[i][i] = 0;//if(ttt == 197) printf("n:%d m:%d k:%d\n",n,m,k);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        G[u][v] = f[u][v] = 1;edge[i] = MP(u,v);
       // if(ttt == 197) printf("%d %d\n",u,v);
    }
    Floyd();
    FOR(i,1,m){
        int u = edge[i].fi,v = edge[i].se;
        if(f[1][u]+f[v][n]+1 <= k) add(u+n,v,1);
    }
    /*FOR(u,1,n){
        FOR(v,1,n){
            if(G[u][v]){
                if(f[1][u]+f[v][n]+1 <= k) add(u+n,v,1);
            }
        }
    }*/
    add(1,1+n,INT_MAX);add(n,n+n,INT_MAX);
    FOR(i,2,n-1) add(i,i+n,1);N = n<<1;int res = Dinic();
    printf("%d\n",res == INT_MAX ? 0 : std::max(res,0));
    clear();
}

int main(){
 //   freopen(".in","r",stdin);
    while(~scanf("%d%d%d",&n,&m,&k) && (n+m+k)) Solve();
    puts("");
    return 0;
}

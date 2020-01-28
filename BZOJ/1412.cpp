/*
 * Time: 2019-12-01 22:59:00
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

const int MAXN = 100+5;

struct Edge{
    int to,nxt,cap,flow;
}e[(MAXN*MAXN*20)<<4];
int head[MAXN*MAXN],cur[MAXN*MAXN],level[MAXN*MAXN],cnt = 1;

inline void add(int u,int v,int cap){
    e[++cnt] = (Edge){v,head[u],cap,0};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

int S,T,N;

inline bool bfs(){
    FOR(i,0,N) cur[i] = head[i],level[i] = 0;
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(!level[e[i].to] && e[i].flow < e[i].cap){
                level[e[i].to] = level[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return 0;
}

inline int dfs(int v,int lim=INT_MAX){
    if(!lim) return 0;
    if(v == T) return lim;
    int flow = 0;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].flow < e[i].cap && level[e[i].to] == level[v] + 1){
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
    int res = 0,flow = 0;
    while(bfs()){
        while((flow = dfs(S))) res += flow;
    }
    return res;
}

int n,m;
int a[MAXN][MAXN];
const int dx[] = {0,0,1,-1};
const int dy[] = {1,-1,0,0};

inline int calc(int x,int y){
    return (x-1)*m+y;
}

int main(){
//    freopen("1.in","r",stdin);
    scanf("%d%d",&n,&m);
    S = n*m+1,N = T = n*m+2;
    FOR(i,1,n) FOR(j,1,m){
        scanf("%d",&a[i][j]);
        if(a[i][j] == 1) add(S,calc(i,j),1e9);
        else if(a[i][j] == 2) add(calc(i,j),T,1e9);
    }
    FOR(x,1,n){
        FOR(y,1,m){
            FOR(k,0,3){
                int xx = x+dx[k],yy = y+dy[k];
                if(xx >= 1 && xx <= n && yy >= 1 && yy <= m){
                    add(calc(x,y),calc(xx,yy),1);
                }
            }
        }
    }
    printf("%d\n",Dinic());
    return 0;
}

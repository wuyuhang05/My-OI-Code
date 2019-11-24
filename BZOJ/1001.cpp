/*
 * Time: 2019-11-23 11:13:04
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
#define P std::pair<LL,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
const int MAXM = 2e6 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXM<<2];

int head[MAXM],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int n,m;
int r[MAXN][MAXN],d[MAXN][MAXN],rd[MAXN][MAXN];
int S,T;
LL dis[MAXM];
bool used[MAXM];

inline int getid(int i,int j,int d){
    return (i-1)*m*2+d*m+j;
}

inline void dij(){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,0,T) dis[i] = 1e18;
    q.push(MP(dis[S] = 0,S));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,n) FOR(j,1,m-1) scanf("%d",&r[i][j]);
    FOR(i,1,n-1) FOR(j,1,m) scanf("%d",&d[i][j]);
    FOR(i,1,n-1) FOR(j,1,m-1) scanf("%d",&rd[i][j]);
    S = n*2*(m-1)+1,T = S+1;
    --n;--m;
    FOR(i,1,m) add(S,getid(1,i,0),r[1][i]);
    FOR(i,1,m) add(getid(n,i,1),T,r[n+1][i]);
    FOR(i,1,n) add(T,getid(i,1,1),d[i][1]);
    FOR(i,1,n) add(getid(i,m,0),S,d[i][m+1]);
    FOR(i,1,n){
        FOR(j,1,m){
            if(j != m) add(getid(i,j,0),getid(i,j+1,1),d[i][j+1]);
            if(i != n) add(getid(i,j,1),getid(i+1,j,0),r[i+1][j]);
            add(getid(i,j,0),getid(i,j,1),rd[i][j]);
        }
    }
    dij();
    printf("%lld\n",dis[T]);
    return 0;
}

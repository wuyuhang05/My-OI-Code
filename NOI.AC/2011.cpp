#pragma GCC optimize("Ofast")
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
#define db double
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

const int MAXN = 1000+5;
int n,q;
int a[MAXN][MAXN];

namespace MCMF{
    struct Edge{
        int fr,to,w,c,nxt;
    }e[MAXN*MAXN+MAXN*3];
    int head[MAXN],cnt=1;

    inline void add(int u,int v,int w,int c){
        e[++cnt] = (Edge){u,v,w,c,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){v,u,0,-c,head[v]};head[v] = cnt;
    }

    LL dis[MAXN];int pre[MAXN];
    bool inq[MAXN];
    int N,S,T;

    inline bool spfa(){
        std::queue<int> q;
        FOR(i,0,N) dis[i] = 1e18,pre[i] = -1;
        dis[S] = 0;pre[S] = 0;q.push(S);inq[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            inq[v] = 0;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && dis[e[i].to] > dis[v]+e[i].c){
//                    DEBUG(e[i].to);DEBUG(e[i].c);
                    dis[e[i].to] = dis[v]+e[i].c;pre[e[i].to] = i;
                    if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = 1;
                }
            }
        }
        return pre[T]!=-1;
    }

    LL maxFlow,minCost;

    inline void work(){
        while(spfa()){
            int flow = 1e9;
            for(int v = T;v != S;v = e[pre[v]].fr){
                flow = std::min(flow,e[pre[v]].w);
            }
            maxFlow += flow;
            for(int v = T;v != S;v = e[pre[v]].fr){
                minCost += 1ll*flow*e[pre[v]].c;
                e[pre[v]].w -= flow;
                e[pre[v]^1].w += flow;
            }
        }
    }
};
using namespace MCMF;

P qq[MAXN*100];
LL ans[MAXN*100];

int main(){
    int cs;scanf("%d",&cs);
    scanf("%d%d",&n,&q);
    FOR(i,1,n) FOR(j,1,n) scanf("%d",&a[i][j]);
    if(cs == 1){
        FOR(i,1,q){
            int C;scanf("%d",&C);
            printf("%d",a[1][1]);printf(".0\n");
        }
        return 0;
    }
    S = 2*n+3;N = T = 2*n+4;
    FOR(i,1,n) FOR(j,1,n) add(i,j+n,1,-a[i][j]);
    FOR(i,1,n) add(2*n+1,i,1,0);
    FOR(i,n+1,2*n) add(i,2*n+2,1,0);
    FOR(i,1,q) scanf("%d",&qq[i].fi),qq[i].se = i;
    std::sort(qq+1,qq+q+1);
    int e1=0,e2=0;
    e1=cnt+1;add(S,2*n+1,0,0);e2=cnt+1;add(2*n+2,T,0,0);
    FOR(i,1,q){
        e[e1].w += qq[i].fi-qq[i-1].fi;
        e[e2].w += qq[i].fi-qq[i-1].fi;
        if(!(i!=1 && qq[i].fi > n))work();
        ans[qq[i].se] = -minCost;
    }
    FOR(i,1,q) printf("%lld.0\n",ans[i]);
    return 0;
}


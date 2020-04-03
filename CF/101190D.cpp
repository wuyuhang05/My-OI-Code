#include<bits/stdc++.h>

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
const int MAXN = 2e5 + 5;

namespace MCMF{
    struct Edge{
        int fr,to,w,c,nxt;
    }e[MAXN<<1];
    int head[MAXN],cnt=1;

    inline void add(int u,int v,int w,int c){
        e[++cnt] = (Edge){u,v,w,c,head[u]};head[u] = cnt;
        e[++cnt] = (Edge){v,u,0,-c,head[v]};head[v] = cnt;
    }

    int dis[MAXN],pre[MAXN];
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
                    dis[e[i].to] = dis[v]+e[i].c;pre[e[i].to] = i;
                    if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = 1;
                }
            }
        }
        return pre[T]!=-1;
    }
    
    int maxFlow,minCost;

    inline void work(){
        while(spfa()){
            int flow = 1e9;
            for(int v = T;v != S;v = e[pre[v]].fr){
                flow = std::min(flow,e[pre[v]].w);
            }
            maxFlow += flow;
            for(int v = T;v != S;v = e[pre[v]].fr){
                minCost += flow*e[pre[v]].c;
                e[pre[v]].w -= flow;
                e[pre[v]^1].w += flow;
            }
        }
    }
}
using namespace MCMF;

int n,k,t1,t2;
int a[MAXN],b[MAXN];
int ps[MAXN];

signed main(){
    freopen("delight.in","r",stdin);
    freopen("delight.out","w",stdout);
    scanf("%lld%lld%lld%lld",&n,&k,&t1,&t2);// 流入-流出
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n) scanf("%lld",b+i);
    N = (n-k+1)*2+1;S = ++N;T = ++N;
    FOR(i,1,n-k+1){
        add(2*i-1,2*i,1e9,0);
        add(2*i+1,2*i,1e9,0);
        add(2*i,T,k-t1-t2,0);
        if(i != 1) add(S,2*i-1,k-t1-t2,0);
    }
    add(1,T,t1,0);add(S,(n-k+1)*2+1,k-t2,0);
    FOR(i,1,n){
        int u = std::max(1ll,(i-k+1)*2-1),v = std::min((n-k+1)*2+1,(i+1)*2-1);
        add(v,u,1,-(a[i]-b[i]));ps[i] = cnt-1;
    }
    work();
    int ans = 0;FOR(i,1,n) ans += b[i];
    ans -= minCost;
    printf("%lld\n",ans);
    FOR(i,1,n) putchar(e[ps[i]].w?'E':'S');
    puts("");
    return 0;
}

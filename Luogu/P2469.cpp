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

const int MAXN = 5e5 + 5;

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
        FOR(i,0,N) dis[i] = 1e9,pre[i] = -1;
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

int a[MAXN],n;
int d[MAXN];

int main(){
    int m;scanf("%d%d",&n,&m);
    N = 2*n;int s = ++N,t = ++N;S = ++N;T = ++N;
    FOR(i,1,n) scanf("%d",a+i),add(s,i,1,a[i]),d[i]++,d[i+n]--,add(i+n,t,1,0);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if(u > v) std::swap(u,v);
        add(u+n,v,1,w);
    }
    int sm = 0;
    FOR(i,1,2*n+2){
        if(d[i] > 0){
            add(i,T,d[i],0);
        }
        if(d[i] < 0){
            add(S,i,-d[i],0);sm -= d[i];
        }
    }
    add(t,s,1e9,0);work();
//    DEBUG(sm);DEBUG(maxFlow);
    printf("%d\n",minCost);
    return 0;
}
/*
 * 点只能经过1次 所以流量是1
 */

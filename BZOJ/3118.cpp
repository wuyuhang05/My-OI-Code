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
const int MAXM = 2e3 + 5;

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
        FOR(i,0,N) dis[i] = -1e9,pre[i] = -1;
        dis[S] = 0;pre[S] = 0;q.push(S);inq[S] = 1;
        while(!q.empty()){
            int v = q.front();q.pop();
            inq[v] = 0;
            for(int i = head[v];i;i = e[i].nxt){
                if(e[i].w > 0 && dis[e[i].to] < dis[v]+e[i].c){
                    dis[e[i].to] = dis[v]+e[i].c;pre[e[i].to] = i;
                    if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = 1;
                }
            }
        }
        return dis[T] >= 0 && pre[T]!=-1;//只要求最大费用 不优的时候就停止增广
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

std::vector<P> G[MAXN];
int dep[MAXN];
int n,m;

struct Node{
    int u,v,w,c,id;
    Node(int u=0,int v=0,int w=0,int c=0,int id=0) : u(u),v(v),w(w),c(c),id(id) {}
};
std::vector<Node> e1,e2;
int fa[MAXN],fae[MAXN];
std::vector<int> cov[MAXN];

inline void dfs(int v){
    dep[v] = dep[fa[v]]+1;
    for(auto x:G[v]){
        if(x.fi == fa[v]) continue;
        fa[x.fi] = v;fae[x.fi] = x.se;dfs(x.fi);
    }
}

inline void jump(int id,int u,int v){
    while(u != v){
        if(dep[u] < dep[v]) std::swap(u,v);
        cov[id].pb(fae[u]);u = fa[u];
    }
}

int main(){
 //   freopen("3.in","r",stdin);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,w,f,a,b;scanf("%d%d%d%d%d%d",&u,&v,&w,&f,&a,&b);
        if(f){
            G[u].pb(MP(v,e1.size()));G[v].pb(MP(u,e1.size()));
            e1.pb(Node(u,v,w,b,i));
        }
        else{
            e2.pb(Node(u,v,w,a,i));
        }
    }
    dfs(1);
    N = m;S = ++N;T = ++N;
    for(auto x:e1) add(S,x.id,x.c,0);
    FOR(i,0,(int)e2.size()-1) jump(i,e2[i].u,e2[i].v),add(e2[i].id,T,e2[i].c,0);
    FOR(i,0,(int)e2.size()-1){
        for(auto j:cov[i]){
            int x = e2[i].id,y = e1[j].id;
            add(y,x,1e9,e1[j].w-e2[i].w);
        }
    }
    work();
    printf("%d\n",minCost);
    return 0;
}

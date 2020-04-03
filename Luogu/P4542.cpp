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
const int MAXM = 200+5;

namespace MCMF{
    struct Edge{
        int fr,to,w,c,nxt;
    }e[MAXN<<1];
    int head[MAXN],cnt=1;

    inline void add(int u,int v,int w,int c){
//        printf("%d %d %d %d\n",u,v,w>10000?-1:w,c);
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

int n,m,k;
int d[MAXN];//出-入
int f[MAXM][MAXM];

inline void addedge(int u,int v,int l,int r,int c){
    d[u] += l;d[v] -= l;
    add(u,v,r-l,c);minCost += l*c;
}

inline int calc(int i,int opt=0){
    return opt*n+i;
}

int main(){
    scanf("%d%d%d",&n,&m,&k);++n;
    FOR(i,1,n) FOR(j,1,n) f[i][j] = i==j?0:1e9;
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);++u;++v;
        f[u][v] = f[v][u] = std::min(f[u][v],w);
    }
    FOR(k,1,n) FOR(i,1,n) FOR(j,1,n) if(k <= i && k <= j) f[i][j] = std::min(f[i][j],f[i][k]+f[k][j]);
    N = 2*n;int s = ++N,t = ++N;S = ++N;T = ++N;
    addedge(s,calc(1),0,k,0);
    FOR(i,1,n) addedge(calc(i,0),calc(i,1),1,1e9,0),addedge(calc(i,1),t,0,k,0);
    FOR(i,1,n){
        FOR(j,i+1,n){
            if(i == j || f[i][j] == 1e9) continue;
            addedge(calc(i,1),calc(j,0),0,1e9,f[i][j]);
        }
    }
    int sm = 0;
    FOR(i,1,2*n+1){
        if(d[i] > 0){
            add(i,T,d[i],0);
        }
        else if(d[i] < 0) add(S,i,-d[i],0),sm -= d[i];//,DEBUG(d[i]);
    }
    add(t,s,1e9,0);
    work();
//    DEBUG(e[2].w);DEBUG(e[cnt-1].w);
    printf("%d\n",minCost);
//    DEBUG(sm);DEBUG(maxFlow);
    return 0;
}

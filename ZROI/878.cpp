/*
 * Author: RainAir
 * Time: 2019-08-05 18:22:57
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5000+5;
const int MAXM = 50000+5;

struct Edge{
    int fr,to,nxt,flow,cap,cost;
}e[MAXM<<1];
int head[MAXN],cnt = 1;

inline void add(int u,int v,int cap,int cost){
    e[++cnt] = (Edge){u,v,head[u],0,cap,cost};head[u] = cnt;
    e[++cnt] = (Edge){v,u,head[v],0,0,-cost};head[v] = cnt;
}

int N,S,T;
int dis[MAXN],pre[MAXN];bool inq[MAXN];

inline bool spfa(){
    FOR(i,0,N) dis[i] = 1e9,inq[i] = false,pre[i] = 0;
    std::queue<int> q;dis[S] = 0;inq[S] = true;q.push(S);
    while(!q.empty()){
        int v = q.front();q.pop();inq[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].cap <= e[i].flow) continue;
            if(dis[e[i].to] > dis[v]+e[i].cost){
                dis[e[i].to] = dis[v]+e[i].cost;
                pre[e[i].to] = i;
                if(!inq[e[i].to]) inq[e[i].to] = true,q.push(e[i].to);
            }
        }
    }
    return pre[T];
}

int maxFlow,minCost;

inline void work(){
    while(spfa()){
        int flow = INT_MAX;
        for(int v = T;v != S;v = e[pre[v]].fr){
            flow = std::min(flow,e[pre[v]].cap-e[pre[v]].flow);
        }
        maxFlow += flow;
        for(int v = T;v != S;v = e[pre[v]].fr){
            e[pre[v]].flow += flow;
            e[pre[v]^1].flow -= flow;
            minCost += e[pre[v]].cost*flow;
        }
    }
}

int n,a[MAXN],rt1,rt2,q1,q2;
std::vector<int> G1[MAXN],G2[MAXN];
int sz1[MAXN],sz2[MAXN],lim1[MAXN],lim2[MAXN];
int f1[MAXN],f2[MAXN];

inline void dfs(int v,int fa,int type){
    (type==1?sz1:sz2)[v] = 1;
    (type==1?f1:f2)[v] = fa;
    for(auto x:(type==1?G1:G2)[v]){
        if(x == fa) continue;
        dfs(x,v,type);
        (type==1?sz1:sz2)[v] += (type==1?sz1:sz2)[x];
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    scanf("%d",&rt1);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G1[u].pb(v);G1[v].pb(u);
    }
    scanf("%d",&rt2);
    FOR(i,1,n-1){
        int u,v;scanf("%d%d",&u,&v);
        G2[u].pb(v);G2[v].pb(u);
    }
    std::fill(lim1,lim1+n+1,-1);std::fill(lim2,lim2+n+1,-1);
    scanf("%d",&q1);
    FOR(i,1,q1){
        int a,q;scanf("%d%d",&a,&q);
        lim1[a] = q;
    }
    scanf("%d",&q2);
    FOR(i,1,q2){
        int a,q;scanf("%d%d",&a,&q);
        lim2[a] = q;
    }
    S = 3*n+1,T = S+1,N = T;
    dfs(rt1,S,1);dfs(rt2,S,2);
    FOR(i,1,n) lim1[i] = lim1[i] == -1 ? sz1[i] : std::min(sz1[i],lim1[i]);
    FOR(i,1,n) lim2[i] = lim2[i] == -1 ? sz2[i] : std::min(sz2[i],lim2[i]);
    FOR(i,1,n){
        add(f1[i],i,lim1[i],0);
        add(f2[i]==S ? f2[i] : f2[i]+n,i+n,lim2[i],0);
        add(i,i+n+n,1,0);add(i+n,i+n+n,1,0);
        add(i+n+n,T,1,-a[i]);
    }
    work();//DEBUG(maxFlow);
    printf("%d\n",-minCost);
    return 0;
}

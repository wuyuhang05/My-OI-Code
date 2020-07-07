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

const int MAXN = 2e5 + 5;

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
int S,T,N;

inline bool spfa(){
    std::queue<int> q;
    FOR(i,0,N) dis[i] = 1e9,pre[i] = -1;
    dis[S] = 0;pre[S] = 0;q.push(S);inq[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();inq[v] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].w > 0 && dis[e[i].to] > dis[v]+e[i].c){
                dis[e[i].to] = dis[v]+e[i].c;
                pre[e[i].to] = i;
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

int n,m,q;
int a[MAXN],b[MAXN],x[MAXN],y[MAXN];

int main(){
    scanf("%d%d%d",&n,&m,&q);
    S = 2*n+1;T = N = 2*n+2;
    FOR(i,1,n){
        scanf("%d%d",a+i,b+i);
        FOR(j,1,q){
            add(i*2-1,i*2,1,a[i]+b[i]*(j-1));
        }
    }
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(u*2,v*2-1,1e9,0);add(v*2,u*2-1,1e9,0);
    }
    FOR(i,1,q){
        int x;scanf("%d",&x);
        add(S,x*2-1,1,0);
    }
    FOR(i,1,q){
        int y;scanf("%d",&y);
        add(y*2,T,1,0);
    }
    work();
    printf("%d\n",minCost);
    return 0;
}

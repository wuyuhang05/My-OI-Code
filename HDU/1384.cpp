#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];

int head[MAXN],dist[MAXN],cnt;
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int N,S,T;

inline void spfa(){
    std::queue<int> q;
    CLR(vis,false);CLR(dist,0x7f);
    q.push(T);dist[T] = 0;vis[T] = true;
    while(!q.empty()){
        int v = q.front();q.pop();
        vis[v] = false;
        for(int i = head[v];i;i = e[i].next){
            if(dist[e[i].to] > dist[v] + e[i].w){
                dist[e[i].to] = dist[v] + e[i].w;
                if(!vis[e[i].to]){
                    vis[e[i].to] = true;
                    q.push(e[i].to);
                }
            }
        }
    }
}

inline void Solve(){
    CLR(head,0);cnt = 0;
    S = INT_MAX,T = INT_MIN;
    FOR(i,1,N){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        T = std::max(T,v+1);
        S = std::min(S,u);
        add(v+1,u,-w);
    }
    FOR(i,1,T){
        add(i,i+1,1);add(i+1,i,0);
    }
    spfa();
    printf("%d\n",-dist[S]);
}

int main(){
    while(~scanf("%d",&N)) Solve();
    return 0;
}


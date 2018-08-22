#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000 + 5;
const int MAXM = 100000 + 5;

struct Edge{
    int to,next;
    double w;
}e[MAXM * 2];

int N,M,A,B;
int head[MAXN],cnt;
bool inQueue[MAXN];
double dist[MAXN];

inline void add(int u,int v,double w){
    e[++cnt].to = v;e[cnt].next = head[u];e[cnt].w = 1.0-w;
    head[u] = cnt;
    e[++cnt].to = u;e[cnt].next = head[v];e[cnt].w = 1.0-w;
    head[v] = cnt;
}

void dijkstra(int S,int T){
    for(int i = 1;i <= N;i++){
        dist[i] = 0;
        inQueue[i] = false;
    }
    std::queue<int> q;
    dist[S] = 1.0;
    inQueue[S] = true;
    q.push(S);
    while(!q.empty()){
        int v = q.front();q.pop();
        inQueue[v] = false;
        for(int i = head[v];i;i = e[i].next){
            if(dist[e[i].to] < dist[v] * e[i].w){
                dist[e[i].to] = dist[v] * e[i].w;
                if(!inQueue[e[i].to]){
                    q.push(e[i].to);
                    inQueue[e[i].to] = true;
                }
            }
        }
    }
}

int main(){
    scanf("%d%d",&N,&M);
    for(int u,v,w,i = 1;i <= M;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,(double)w/100);
    }
    scanf("%d%d",&A,&B);
    dijkstra(A,B);
    double ans = 100/(dist[B]);
    printf("%.8f",ans);
    return 0;
}

#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

const int MAXN = 30000 + 5;
const int MAXM = 50010 + 5;
const int INF = 1e9 + 7;
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

struct Edge{
    int to,w,next;
}e[MAXM * 2];

int N,M;
int head[MAXN],inQueue[MAXN],dist[MAXN],cnt;

inline void Read(int &x){
    char ch = getchar();
    x = 0;int flag = 0;
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = getchar();
    }
    while(isdigit(ch)){
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    x = (flag == 1) ? -x : x;
}

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};
    head[u] = cnt;
}

void spfa(){
    for(int i = 0;i <= N + 1;i++){
        inQueue[i] = false;
        dist[i] = INF;
    }
    std::queue<int> q;
    q.push(N + 1);
    dist[N + 1] = 0;
    inQueue[N + 1] = true;
    while(!q.empty()){
        int v = q.front();q.pop();
        inQueue[v] = false;
        for(int i = head[v];i != -1;i = e[i].next){
            if(dist[e[i].to] > dist[v] + e[i].w){
                dist[e[i].to] = dist[v] + e[i].w;
                if(!inQueue[e[i].to]){
                    q.push(e[i].to);
                    inQueue[e[i].to] = true;
                }
            }
        }
    }
}

int main(){
    Read(N);Read(M);
    memset(head,-1,sizeof(head));
    for(int u,v,w,i = 1;i <= M;i++){
        Read(u);Read(v);Read(w);
        add(v,u-1,-w);
    }
    for(int i = 0;i <= N;i++)
        add(N + 1,i,0);
    for(int i = 1;i <= N;i++){
        add(i-1,i,1);
        add(i,i-1,0);
    }
    spfa();
    int min = INF;
    for(int i = 0;i <= N + 1;i++)
        min = (dist[i] < min) ? dist[i] : min;
    printf("%d",dist[N] - min);
    return 0;
}

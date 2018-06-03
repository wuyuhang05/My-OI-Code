#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

const int MAXN = 100000 + 5;

struct Edge{
    int to,w,next;
}e[MAXN * 2];

int head[MAXN],cnt;
int dist[MAXN];
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = Edge{v,w,head[u]};
    head[u] = cnt;
    e[++cnt] = Edge{u,w,head[v]};
    head[v] = cnt;
}

int N,M;

void dfs(int id,int val){
    dist[id] = val;
    vis[id] = true;
    for(int i = head[id];i;i = e[i].next){
        if(!vis[e[i].to])
            dfs(e[i].to,val ^ e[i].w);
    }
}

int main(){
    scanf("%d",&N);
    for(int u,v,w,i = 1;i < N;i++){
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    dfs(1,0);
    scanf("%d",&M);
    while(M--){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",(dist[x] ^ dist[y]));
    }
    return 0;
}

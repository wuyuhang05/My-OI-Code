#include <iostream>
#include <cstdio>
#include <cstring>

const int MAXN = 300000 + 5;
const int MAXM = 300000 + 5;

struct Edge{
    int to,w,next;
}e[MAXN * 2];
int head[MAXN],edge_size;

inline void add(int u,int v,int w){
    e[++edge_size] = (Edge){v,w,head[u]};
    head[u] = edge_size;
}

int f[MAXN],deep[MAXN],size[MAXN];

void dfs(int v){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next)
        if(e[i].to != f[v]){
            f[e[i].to] = v;
            deep[e[i].to] = deep[v] + 1;
            dfs(e[i].to);
            size[v] += size[e[i].to];
        }
}

int main(){
    return 0;
}

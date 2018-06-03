#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

const int MAXN = 1000 + 5;

std::vector<int> g[MAXN];
int low[MAXN],dfn[MAXN],dg[MAXN],timer;
bool vis[MAXN],map[MAXN][MAXN];
int N,R;

void dfs(int v,int fa){
    low[v] = dfn[v] = ++timer;
    vis[v] = true;
    for(int i = 0;i < g[v].size();i++){
        if(g[v][i] == fa) continue;
        if(!dfn[g[v][i]]){
            dfs(g[v][i],v);
            low[v] = std::min(low[v],low[g[v][i]]);
        }
        else if(vis[g[v][i]]){
            low[v] = std::min(low[v],dfn[g[v][i]]);
        }
    }
}

void get(){
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(vis,false,sizeof(vis));
    timer = 0;
    for(int i = 1;i <= N;i++){
        if(!dfn[i]) dfs(i,-1);
    }
}

int main(){
    while(scanf("%d%d",&N,&R) != EOF){
        for(int i = 1;i <= N;i++)
            g[i].clear();
        memset(map,0,sizeof(map));
        for(int u,v,i = 0;i < R;i++){
            scanf("%d%d",&u,&v);
            if(!map[u][v]){
                g[u].push_back(v);
                g[v].push_back(u);
                map[u][v] = map[v][u] = true;
            }
        }
        get();
        memset(dg,0,sizeof(dg));
        for(int v = 1;v <= N;v++){
            for(int i = 0;i < g[v].size();i++){
                if(low[v] != low[g[v][i]]){
                    dg[low[v]]++;
                }
            }
        }
        int tot = 0;
        for(int i = 1;i <= N;i++){
            if(dg[i] == 1)
                tot++;
        }
        printf("%d\n",(tot + 1) / 2);
    }
    return 0;
}

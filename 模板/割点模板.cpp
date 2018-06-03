#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>

const int MAXN = 100000 + 5;

int N,M,cnt,ans;
int dfn[MAXN],low[MAXN],head[MAXN],fa[MAXN];
bool cut[MAXN];

struct Edge{
    int to,next;
}e[MAXN * 2];

void add(int u,int v){
    e[++cnt] = (Edge) {v,head[u]};
    head[u] = cnt;
}

void dfs(int v){
    int rd = 0;
    dfn[v] = low[v] = ++cnt;
    for(int i = head[v];i;i = e[i].next){
        if(!dfn[e[i].to]){
            fa[e[i].to] = fa[v];
            dfs(e[i].to);
            low[v] = std::min(low[v],low[e[i].to]);
            if(low[e[i].to] >= dfn[v] && v != fa[v])
                cut[v] = true;
            if(v == fa[v]) rd++;
        }
        low[v] = std::min(low[v],dfn[e[i].to]);
    }
    if(v == fa[v] && rd >= 2)
        cut[fa[v]] = true;
}

int main(){
    int N,M;
    scanf("%d%d",&N,&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    cnt = 0;
    for(int i = 1;i <= N;i++)
        fa[i] = i;
    for(int i = 1;i <= N;i++){
        if(!dfn[i]) dfs(i);
    }
    for(int i = 1;i <= N;i++){
        if(cut[i]) ans++;
    }
    printf("%d\n",ans);
    for(int i = 1;i <= N;i++){
        if(cut[i]) printf("%d ",i);
    }
    return 0;
}

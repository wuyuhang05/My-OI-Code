#include <algorithm>
#include <iostream>
#include <climits>
#include <cstring>
#include <cstdio>

const int MAXN = 10000 + 5;
const int MAXM = 50000 + 5;

struct Tree{
    int to,next,w;
}t[MAXM];

struct Side{
    int u,v,w;

    bool operator < (const Side &x) const{
        return w > x.w;
    }
}e[MAXM];

int N,M,log2N;
int head[MAXN],cnt;
int fa[MAXN],deep[MAXN];
bool check[MAXN];
int f[MAXN][20 + 5],w[MAXN][20 + 5];

inline void addTree(int u,int v,int w){
    t[++cnt] = Tree{v,head[u],w};
    head[u] = cnt;
    t[++cnt] = Tree{u,head[v],w};
    head[v] = cnt;
}

inline void init(){
    for(int i = 1;i <= N;i++)
        fa[i] = i;
}

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void Union(int x,int y){
    fa[find(x)] = find(y);
}

void KrusKal(){
    init();
    std::sort(e + 1,e + M + 1);
    int cnt = 0;
    for(int i = 1;i <= M;i++){
        if(find(e[i].u) != find(e[i].v)){
            Union(e[i].u,e[i].v);
            addTree(e[i].u,e[i].v,e[i].w);
            cnt++;
        }
        if(cnt == N - 1) break;
    }
}

void dfs(int v,int fa,int d){
    check[v] = true;
    f[v][0] = fa;
    deep[v] = d;
    for(int i = head[v];i;i = t[i].next){
        if(!check[t[i].to]){
            w[t[i].to][0] = t[i].w;
            dfs(t[i].to,v,d + 1);
        }
    }
}

void ycl(){
    for(int i = 1;i <= N;i++)
        if(!check[i])
            dfs(i,0,1);
    for(int j = 1;j <= 20;j++){
        for(int i = 1;i <= N;i++){
            f[i][j] = f[f[i][j-1]][j-1];
            w[i][j] = std::min(w[i][j-1],w[f[i][j-1]][j-1]);
        }
    }
}

int lca(int x,int y){
    if(deep[x] < deep[y]) std::swap(x,y);
    int ret = INT_MAX;
    for(int i = 20;i >= 0;i--){
        if(deep[f[x][i]] >= deep[y]){
            ret = std::min(ret,w[x][i]);
            x = f[x][i];
        }
    }
    if(x == y) return ret;
    for(int i = 20;i >= 0;i--){
        if(f[x][i] != f[y][i]){
            ret = std::min(ret,std::min(w[x][i],w[y][i]));
            x = f[x][i];
            y = f[y][i];
        }
    }
    return ret = std::min(ret,std::min(w[x][0],w[y][0]));
}

void query(){
    int q;
    scanf("%d",&q);
    while(q--){
        int x,y;
        scanf("%d%d",&x,&y);
        if(find(x) != find(y))
            printf("-1\n");
        else
            printf("%d\n",lca(x,y));
    }
}

int main(){
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= M;i++)
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    KrusKal();
    ycl();
    query();
    return 0;
}

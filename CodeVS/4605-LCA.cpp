#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

const int MAXN = 100000 + 5;

struct Edge{
    int to,next;
}e[MAXN * 2];

int head[MAXN],deep[MAXN],cnt,root,log2n,LastAns;
bool used[MAXN];
int f[MAXN][32];
int N,M;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};
    head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};
    head[v] = cnt;
}

inline void init(){
    memset(f,-1,sizeof(f));
    memset(used,false,sizeof(used));
    memset(deep,0,sizeof(deep));
    log2n = log(N) / log(2) + 1;
}

void dfs(int v,int h){
    deep[v] = h;
    for(int i = 1;i <= log2n;i++){
        if(h <= (1 << i)) break;
        f[v][i] = f[f[v][i-1]][i-1];
    }
    for(int i = head[v];i;i = e[i].next){
        if(!used[e[i].to]){
            used[e[i].to] = true;
            f[e[i].to][0] = v;
            dfs(e[i].to,h + 1);
        }
    }
}

int lca(int a,int b){
    int da = deep[a],db = deep[b];
    if(da != db){
        if(da < db){
            std::swap(a,b);
            std::swap(da,db);
        }
        int d = da - db;
        for(int i = 0;i <= log2n;i++){
            if((1 << i) & d)
                a = f[a][i];
        }
    }
    if(a == b) return b;
    for(int i = log2n;i >= 0;i--){
        if(deep[f[a][i]] < 0)
            continue;
        if(f[a][i] == f[b][i])
            continue;
        else a = f[a][i],b = f[b][i];
    }
    return f[a][0];
}

int main(){
    scanf("%d",&N);
    for(int x,i = 1;i <= N;i++){
        scanf("%d",&x);
        if(x == 0) root = i;
        else add(x,i);
    }
    init();
    used[root] = true;
    dfs(root,1);
    scanf("%d",&M);
    while(M--){
        int x,y;
        scanf("%d%d",&x,&y);
        LastAns = lca(x^LastAns,y^LastAns);
        printf("%d\n",LastAns);
    }
    getchar();getchar();
    return 0;
}

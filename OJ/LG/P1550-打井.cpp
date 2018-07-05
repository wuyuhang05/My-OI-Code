#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 300 + 5;

struct Edge{
    int u,v,w;
    
    bool operator < (const Edge &other) const{
        return w < other.w;
    }
}e[MAXN*MAXN];

int N,M,ans,cnt;
int f[MAXN],map[MAXN][MAXN];

void init(){
    for(int i = 1;i <= N;i++)
        f[i] = i;
}

int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++){
        scanf("%d",&e[++M].w);
        e[M].u = 0;e[M].v = i;
    }
    init();
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            scanf("%d",&map[i][j]);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j < i;j++)
            e[++M] = (Edge){i,j,map[i][j]};
    std::sort(e + 1,e + M + 1);
    for(int i = 1;i <= M;i++){
        int fu = find(e[i].u),fv = find(e[i].v);
        if(fu == fv) continue;
        ans += e[i].w;
        f[fu] = fv;
        if(++cnt == N) break;
    }
    printf("%d\n",ans);
    //DEBUG(cnt);DEBUG(M);
    return 0;
}

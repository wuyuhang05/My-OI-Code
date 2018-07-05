#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 200 + 5;
const int MAXM = 200000 + 5;

int map[MAXN][MAXN];
int N,M;
struct Edge{
    int u,v,w;
    
    bool operator < (const Edge &other) const{
        return w < other.w;
    }
}e[MAXM * 2];

int f[MAXN],cnt,ans;

inline void init(){
    for(int i = 1;i <= N;i++)
        f[i] = i;
}

int find(int x){
    return f[x] == x ? f[x] : f[x] = find(f[x]);
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            scanf("%d",&map[i][j]);
    for(int i = 1;i <= N;i++){
        for(int j = 1;j < i;j++){
            e[++M] = (Edge){i,j,map[i][j]};
        }
    }
    std::sort(e + 1,e + M + 1);
    init();
    for(int i = 1;i <= M;i++){
        int fu = find(e[i].u),fv = find(e[i].v);
        if(fu == fv) continue;
        ans += e[i].w;
        cnt++;
        f[fu] = fv;
        if(cnt == N - 1) break;
    }
    printf("%d\n",ans);
    return 0;
}

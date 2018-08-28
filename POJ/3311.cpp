#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 20 + 5;
int N;

int dist[MAXN][MAXN],cost[MAXN][MAXN];
int f[MAXN][1<<15];
bool vis[MAXN][1<<15];

void floyd(){
    for(int k = 0;k <= N;k++)
        for(int i = 0;i <= N;i++)
            for(int j = 0;j <= N;j++)
                cost[i][j] = std::min(cost[i][j],cost[i][k] + cost[k][j]);
}

int dp(int i,int s){
    if(vis[i][s]) return f[i][s];
    vis[i][s] = true;
    int &ans = f[i][s];
    ans = 1e9;
    for(int j = 0;j <= N;j++)
        if(s & (1 << j) && j != i){
            ans = std::min(ans,dp(j,s^(1 << i)) + cost[j][i]);
        }
    return ans;
}

int main(){
    while(scanf("%d",&N) == 1 && N){
        for(int i = 0;i <= N;i++)
            for(int j = 0;j <= N;j++){
                scanf("%d",&dist[i][j]);
                cost[i][j] = dist[i][j];
            }
        floyd();
        memset(vis,false,sizeof(vis));
        f[0][0] = 0;
        vis[0][0] = true;
        for(int i = 1;i <= N;i++){
            vis[i][1<<i] = true;
            f[i][1<<i] = cost[0][i];
        }
        printf("%d\n",dp(0,(1 << (N + 1)) - 1));
    }
    return 0;
}


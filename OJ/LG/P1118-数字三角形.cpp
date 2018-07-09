#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 12 + 5;

int N,sum,ans[MAXN];
int yh[MAXN][MAXN];
bool vis[MAXN],flag;

void dfs(int step,int s){
    if(flag) return;
    if(s > sum) return;
    if(step == N + 1){
        if(s == sum){
            for(int i = 1;i <= N;i++)
                printf("%d%c",ans[i],(i == N) ? '\n' : ' ');
            flag = true;
        }
        return;
    }
    for(int i = 1;i <= N;i++){
        if(!vis[i]){
            ans[step] = i;
            s += yh[N][step] * ans[step];
            vis[i] = true;
            dfs(step + 1,s);
            s -= yh[N][step] * ans[step];
            vis[i] = false;
        }
    }
}

int main(){
    scanf("%d%d",&N,&sum);
    yh[1][1] = 1;
    for(int i = 2;i <= N;i++)
        for(int j = 1;j <= i;j++)
            yh[i][j] = yh[i-1][j] + yh[i-1][j-1];
    dfs(1,0);
    return 0;
}


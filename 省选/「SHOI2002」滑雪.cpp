#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>

const int MAXN = 200 + 5;

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

int map[MAXN][MAXN];
int f[MAXN][MAXN];
int ans;
int R,C;

inline void init(){
    for(int i = 0;i <= C + 1;i++)
        map[i][0] = map[i][C + 1] = INT_MAX;
    for(int i = 0;i <= R + 1;i++)
        map[0][i] = map[R + 1][i] = INT_MAX;
}

int dfs(int x,int y){
    if(f[x][y]) return f[x][y];
    f[x][y] = 1;
    for(int i = 0;i < 4;i++){
        int xx = x + dx[i],yy = y + dy[i];
        if(map[x][y] > map[xx][yy])
            f[x][y] = std::max(f[x][y],dfs(xx,yy) + 1);
    }
    return f[x][y];
}

int main(){
    scanf("%d%d",&R,&C);
    init();
    for(int i = 1;i <= R;i++)
        for(int j = 1;j <= C;j++)
            scanf("%d",&map[i][j]);
    for(int i = 1;i <= R;i++)
        for(int j = 1;j <= C;j++)
            ans = std::max(ans,dfs(i,j));
    printf("%d",ans);
    //getchar();getchar();
    return 0;
}

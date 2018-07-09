#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

const int MAXN = 30 + 5;

const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

int N;
int map[MAXN][MAXN];

void bfs(){
    std::queue<std::pair<int,int> > q;
    for(int i = 1;i <= N;i++)
        (for(int j = 1;j <= N;j++){
            if(((i == 1 || i == N) || (j == 1 || j == N)) && map[i][j] == 0){
                q.push(std::make_pair(i,j));
                map[i][j] = -1;
            }
        }
    while(!q.empty()){
        std::pair<int,int> u = q.front();
        q.pop();
        for(int i = 0;i < 4;i++){
            std::pair<int,int> v = std::make_pair(u.first + dx[i],u.second + dy[i]);
            if(map[v.first][v.second] != 0) continue;
            map[v.first][v.second] = -1;
            q.push(v);
        }
    }
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            scanf("%d",&map[i][j]);
    bfs();
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            printf("%d%c",map[i][j] == -1 ? 0 : map[i][j] == 1 ? 1 : 2,(j == N) ? '\n' : ' ');
    return 0;
}


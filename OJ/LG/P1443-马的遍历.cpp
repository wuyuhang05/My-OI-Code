#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

const int MAXN = 400 + 5;
const int dx[8] = {1,2,-1,-2,1,-1,2,-2};
const int dy[8] = {2,1,-2,-1,-2,2,-1,1};

int N,M;
int sx,sy;
int map[MAXN][MAXN];

struct Node{
    int x,y,ts;
};

void bfs(){
    std::queue<Node> q;
    q.push((Node){sx,sy,0});
    map[sx][sy] = 0;
    while(!q.empty()){
        Node u = q.front();
        q.pop();
        for(int i = 0;i < 8;i++){
            Node v = (Node){u.x + dx[i],u.y + dy[i],u.ts + 1};
            if(v.x <= 0 || v.x > N || v.y <= 0 || v.y > M ||map[v.x][v.y] != -1) continue;
            map[v.x][v.y] = v.ts;
            q.push(v);
        }
    }
}

int main(){
    scanf("%d%d%d%d",&N,&M,&sx,&sy);
    memset(map,-1,sizeof(map));
    bfs();
    for(int i = 1;i <= N;i++,puts(""))
        for(int j = 1;j <= M;j++)
            printf("%-5d",map[i][j]);
    return 0;
}


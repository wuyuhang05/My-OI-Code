#include <iostream>
#include <cstdio>
#include <cstring>
#include <climits>
#include <stack>

const int MAXN = 200 + 5;
const int MAXM = 200 + 5;
const int INF = 1000000000;

int N,M;
int map[MAXN][MAXN],f[MAXN][MAXN],cnt[MAXN][MAXN];
struct Edge{
    int x,y;

    Edge(int x=0,int y=0) : x(x), y(y) {}
}e[MAXM];
int top;

std::stack<int> s;

int get(){
    int ret = 0;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= N;j++){
            if(i != j && f[i][j] == INF)
                return INF;
            else
                ret += f[i][j];
        }
    }
    return ret;
}

int main(){
    scanf("%d",&N);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++){
            scanf("%d",&map[i][j]);
            f[i][j] = map[i][j];
        }
    scanf("%d",&M);
    for(int u,v,i = 1;i <= M;i++){
        scanf("%d%d",&u,&v);
        f[u][v] = INF;
        cnt[u][v]++;
        e[++top] = Edge(u,v);
    }
    for(int k = 1;k <= N;k++)
        for(int i = 1;i <= N;i++)
            for(int j = 1;j <= N;j++)
                f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
    for(int i = 1;i <= M;i++){
        s.push(get());
        cnt[e[top].x][e[top].y]--;
        if(cnt[e[top].x][e[top].y] == 0){
            f[e[top].x][e[top].y] = std::min(f[e[top].x][e[top].y],map[e[top].x][e[top].y]);
        }
        for(int j = 1;j <= N;j++){
            for(int k = 1;k <= N;k++){
                f[j][k] = std::min(f[j][k],f[j][e[top].x] + f[e[top].x][e[top].y] + f[e[top].y][k]);
            }
        }
        top--;
    }
    while(!s.empty()){
        if(s.top() == INF)
            puts("INF");
        else
            printf("%d\n",s.top());
        s.pop();
    }
    getchar();getchar();
    return 0;
}

#include <iostream>
#include <cstdio>
#include <climits>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cstdlib>

const int MAXN = 12 + 5;

int map[MAXN][MAXN],depth[MAXN];

struct Edge{
    int u,v;
    bool operator < (const Edge other) const{
        return depth[u] * map[u][v] > depth[other.u] * map[other.u][other.v];
    }
};

int N,M;

int search(int x){
    memset(depth,0,sizeof(depth));
    bool vis[MAXN] = {false};
    std::priority_queue<struct Edge> h;
    Edge past[1000 + 5];int p = 0;
    struct Edge e,e2;
    int cost = 0;
    depth[x] = 1;
    vis[x] = true;
    for(int i = 1;i <= N;i++){
        if(map[x][i] != INT_MAX){
            e.u = x;e.v = i;
            h.push(e);
        }
    }
    for(int i = 1;i < N;i++){
        e = h.top();h.pop();
        while(!h.empty() && ((vis[e.v] || rand() % (N) < 1))){
            if(!vis[e.v]) past[p++] = e;
            e = h.top();h.pop();
        }
        vis[e.v] = true;
        depth[e.v] = depth[e.u] + 1;
        if(p-- > 0)
            for(;p >= 0;--p)
                h.push(past[p]);
        p = 0;
        for(int i = 1;i <= N;i++){
            if(map[e.v][i] != INT_MAX && !vis[i]){
                e2.u = e.v;e2.v = i;
                h.push(e2);
            }
        }
        cost += map[e.u][e.v] * depth[e.u];
    }
    return cost;
}

int main(){
    scanf("%d%d",&N,&M);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= N;j++)
            map[i][j] = INT_MAX;
    for(int a,b,c,i = 1;i <= M;i++){
        scanf("%d%d%d",&a,&b,&c);
        map[a][b] = map[b][a] = std::min(c,map[a][b]);
    }
    srand(10086);
    int ans = INT_MAX;
    for(int j = 1;j < 1000;j++){
        for(int i = 1;i <= N;i++){
            ans = std::min(ans,search(i));
        }
    }
    printf("%d\n",ans);
    return 0;
}

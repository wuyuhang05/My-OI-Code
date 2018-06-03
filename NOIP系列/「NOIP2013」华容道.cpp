#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <queue>

const int MAXN = 4000 + 5;

const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

int N,M,Q,cnt;
int map[33][33],cost[33][33],head[MAXN];
std::queue<std::pair<int,int>> q;

struct Edge{
    int to,w,next;
}e[MAXN * 10];
int dist[MAXN],inQueue[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};
    head[u] = cnt;
}

void bfs(int sx,int sy,int bx,int by,int fx){
    memset(cost,0,sizeof(cost));
    q.push(std::make_pair(sx,sy));
    cost[sx][sy] = 1;
    while(!q.empty()){
        int x = q.front().first,y = q.front().second;
        for(int i = 0;i < 4;i++){
            int xx = x + dx[i],yy = y + dy[i];
            if(map[xx][yy] && !cost[xx][yy] && (xx != bx || yy != by)){
                cost[xx][yy] = cost[x][y] + 1;
                q.push(std::make_pair(xx,yy));
            }
        }
        q.pop();
    }
    if(fx == 4) return;
    for(int i = 0;i < 4;i++){
        int x = bx + dx[i],y = by + dy[i];
        if((x != sx || y != sy) && cost[x][y])
            add(bx * 120 + by * 4 + fx,bx * 120 + by * 4 + i,cost[x][y] - 1);
    }
    add(bx * 120 + by * 4 + fx,sx * 120 + sy * 4 + fx ^ 1,1);
}
/*void bfs(int sx,int sy,int bx,int by,int fx){//(sx,sy):空格位置，(bx,by):目标棋子位置
    int i,ta=1,he=1,xx,yy,tx,ty;
    memset(cost,0,sizeof(cost));
    qx[1]=sx,qy[1]=sy,dis[sx][sy]=1;
    q.push()
    while(he<=ta){
        xx=qx[he],yy=qy[he];
        for(i=0;i<=3;++i){
            tx=xx+mvx[i],ty=yy+mvy[i];
            if(mp[tx][ty]&&!dis[tx][ty]&&(tx!=bx||ty!=by))//注意这些限制条件
                dis[tx][ty]=dis[xx][yy]+1,qx[++ta]=tx,qy[ta]=ty;
        }
        ++he;
    }
    if(fx==4)return;
    for(i=0;i<=3;++i){//情况1：空格在不经过目标棋子的情况下来到目标棋子身边其他方位
        tx=bx+mvx[i],ty=by+mvy[i];
        if((tx!=sx||ty!=sy)&&dis[tx][ty])
            add(bx*120+by*4+fx,bx*120+by*4+i,dis[tx][ty]-1);
    }
    add(bx*120+by*4+fx,sx*120+sy*4+fx^1,1);//情况2：交换空格与目标棋子的位置
}
*/
void spfa(int x,int y){
    std::queue<int> q;
    for(int i = 0;i <= 4000;i++){
        dist[i] = INT_MAX;
        inQueue[i] = false;
    }
    for(int i = 0;i < 4;i++){
        int xx = x + dx[i],yy = y + dy[i],tt = x * 120 + y * 4 + i;
        if(cost[xx][yy]){
            dist[tt] = cost[xx][yy] - 1;
            q.push(tt);
            inQueue[tt] = true;
        }
    }
    while(!q.empty()){
        int v = q.front();
        q.pop();
        inQueue[v] = false;
        for(int i = head[v];i != -1;i = e[i].next){
            if(dist[e[i].to] > dist[v] + e[i].w){
                dist[e[i].to] = dist[v] = e[i].w;
                if(!inQueue[e[i].to]){
                    q.push(e[i].to);
                    inQueue[e[i].to] = true;
                }
            }
        }
    }
}

int main(){
    scanf("%d%d%d",&N,&M,&Q);
    memset(head,-1,sizeof(head));
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= M;j++)
            scanf("%d",&map[i][j]);
    for(int i = 1;i <= N;i++)
        for(int j = 1;j <= M;j++){
            if(!map[i][j]) continue;
            if(map[i-1][j]) bfs(i-1,j,i,j,0);
            if(map[i+1][j]) bfs(i+1,j,i,j,1);
            if(map[i][j-1]) bfs(i,j-1,i,j,2);
            if(map[i][j+1]) bfs(i,j+1,i,j,3);
        }
    while(Q--){
        int sx,sy,bx,by,mx,my,ans = INT_MAX;
        scanf("%d%d%d%d%d%d",&sx,&sy,&bx,&by,&mx,&my);
        if(bx == mx && by == my){
            puts("0");
            continue;
        }
        bfs(sx,sy,bx,by,4);
        spfa(bx,by);
        for(int i = 0;i < 4;i++)
            ans = std::min(ans,dist[mx * 120 + my * 4 + i]);
        if(ans < INT_MAX)
            printf("%d\n",ans);
        else
            puts("-1");
    }
    return 0;
}

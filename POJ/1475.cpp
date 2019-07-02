#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20+5;
const int MAXM = 2e6 + 3;
/*
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};
const char du[4] = {'E','W','S','N'};
const char dl[4] = {'e','w','s','n'};
*/

const int dx[4] = {-1,0,1,0};
const int dy[4] = {0,1,0,-1};
const char du[4] = {'N','E','S','W'};
const char dl[4] = {'n','e','s','w'};

int n,m;
char mp[MAXN][MAXN];
int pre[MAXM];
bool vis[MAXN][MAXN][MAXN][MAXN]; // 状态vis[x1][y1][x2][y2]是否到达
char ans[MAXM];

struct Node{
    int x1,y1; // 人
    int x2,y2; // 箱子
    int dis,cnt,id;

    bool operator < (const Node &t) const {
        return cnt == t.cnt ? dis > t.dis : cnt > t.cnt;
    }
}s,t;

inline int bfs(){
    std::priority_queue<Node> q;
    s.dis = 0;s.cnt = 0;s.id = 0;q.push(s);vis[s.x1][s.y1][s.x2][s.y2] = true;
    pre[0] = -1;int tot = 1;
    while(!q.empty()){
        Node v = q.top();q.pop();
        if(v.x2 == t.x2 && v.y2 == t.y2) return v.id;
        FOR(i,0,3){
            Node t = v;
            t.x1 += dx[i],t.y1 += dy[i];
            int x = t.x1,y = t.y1;//DEBUG(x);DEBUG(y);
            if(x >= 1 && x <= n && y >= 1 && y <= m && mp[x][y] != '#'){
                if(x == t.x2 && y == t.y2){
                    int xx = x+dx[i],yy = y+dy[i];
                    if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && mp[xx][yy] != '#'){
                        if(!vis[x][y][xx][yy]){
                            t.x2 = xx;t.y2 = yy;pre[tot] = t.id;t.id = tot++;
                            t.dis = v.dis + 1;t.cnt = v.cnt+1;q.push(t);
                            ans[t.id] = du[i];vis[x][y][xx][yy] = true;
                        }
                    }
                }
                else{
                    if(!vis[x][y][t.x2][t.y2]){
                        pre[tot] = t.id;t.id = tot++;
                        t.dis = v.dis+1;q.push(t);ans[t.id] = dl[i];
                        vis[x][y][t.x2][t.y2] = true;
                    }
                }
            }
        }
    }
    return -1;
}

inline void dfs(int v){
    if(pre[v] != -1){
        dfs(pre[v]);
        printf("%c",ans[v]);
    }
}

inline void init(){
    CLR(pre,0);CLR(vis,0);CLR(ans,0);
}

inline void Solve(){
    init();
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        scanf("%s",mp[i]+1);
        FOR(j,1,m){
            if(mp[i][j] == 'S') s.x1 = i,s.y1 = j;
            if(mp[i][j] == 'T') t.x2 = i,t.y2 = j;
            if(mp[i][j] == 'B') s.x2 = i,s.y2 = j;
            if(mp[i][j] != '#') mp[i][j] = '.';
        }
    }
    int v = bfs();
    if(v == -1) printf("Impossible.");
    else dfs(v);puts("");puts("");
}

int main(){
 //   freopen("b.out","w",stdout);
    int cas = 0;
    while(~scanf("%d%d",&n,&m)){
        if(n == 0 && m == 0) return 0;
      //  if(cas) puts("");
        printf("Maze #%d\n",++cas);Solve();
    }
}

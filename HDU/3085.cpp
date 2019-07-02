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

const int MAXN = 800+5;
const int dx[4] = {0,0,1,-1};
const int dy[4] = {1,-1,0,0};

char str[MAXN][MAXN];
int n,m;

struct Node{
    int x,y;
    Node(){}
    Node(int x,int y) : x(x),y(y) {}

    inline void print(){
        printf("%d %d\n",x,y);
    }
}g[3],G,M;

inline int dis(const Node &a,const Node &b){
    return std::abs(a.x-b.x) + std::abs(a.y-b.y);
}

inline bool pd(const Node &t,int ts){
    if(dis(t,g[1]) <= 2*ts) return false;
    if(dis(t,g[2]) <= 2*ts) return false;
    return true;
}

std::queue<Node> q[2];
bool vis[2][MAXN][MAXN];

inline bool ext(int id,int ts){
    int times = q[id].size();
    while(times--){
        Node v = q[id].front();q[id].pop();
        int x = v.x,y = v.y;//DEBUG(pd(v,ts));
        if(!pd(v,ts)) continue;
        FOR(i,0,3){
            int xx = x+dx[i],yy = y+dy[i];Node t = Node(xx,yy);
            if(xx >= 1 && xx <= n && yy >= 1 && yy <= m && str[xx][yy] != 'X' && str[xx][yy] != 'Z' && !vis[id][xx][yy] && pd(t,ts)){   
                vis[id][xx][yy] = true;
                if(vis[!id][xx][yy]) return true;
                q[id].push(t);
            }
        }
    }
    return false;
}

inline int bfs(){
    CLR(vis,0);
    while(!q[0].empty()) q[0].pop();
    while(!q[1].empty()) q[1].pop();
    vis[0][M.x][M.y] = vis[1][G.x][G.y] = true;
    q[0].push(M);q[1].push(G);
    int ts = 0;
    while(!q[0].empty() || !q[1].empty()){
        ts++;
        FOR(i,1,3) if(ext(0,ts)) return ts;
        if(ext(1,ts)) return ts;
    }
    return -1;
}

inline void init(){
    FOR(i,0,1) while(!q[i].empty()) q[i].pop();
    CLR(vis,0);
}

inline void Solve(){
    init();
    scanf("%d%d",&n,&m);int cnt = 0;
    FOR(i,1,n){
        scanf("%s",str[i]+1);
        FOR(j,1,m){
            if(str[i][j] == 'Z') g[++cnt] = Node(i,j);
            if(str[i][j] == 'G') G = Node(i,j);
            if(str[i][j] == 'M') M = Node(i,j);
        }
    }
  //  G.print();M.print();g[1].print();g[2].print();
    printf("%d\n",bfs());
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

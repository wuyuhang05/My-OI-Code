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
#define P std::pair<int,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
const int MAXM = 10000+5;

struct Node{
    int v,dis;bool flag;
    Node(){}
    Node(int v,int dis,bool flag) : v(v),dis(dis),flag(flag) {}

    bool operator < (const Node &t) const {
        return dis > t.dis;
    }
};

struct Edge{
    int to,w,nxt;
}e[MAXM<<2];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int n,m,S,T;
int dis[2][MAXN],vis[2][MAXN],f[2][MAXN];

inline void dij(){
    std::priority_queue<Node> q;
    FOR(i,1,n) dis[0][i] = dis[1][i] = INT_MAX;
    dis[0][S] = 0;f[0][S] = 1;q.push(Node(S,0,false));
    while(!q.empty()){
        Node now = q.top();q.pop();
        int val = now.dis,v = now.v;bool o = now.flag;
        if(vis[o][v]) continue;vis[o][v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            int x = e[i].to,gx = val + e[i].w;
            if(gx < dis[0][x]){
                if(dis[0][x] != INT_MAX){
                    dis[1][x] = dis[0][x];f[1][x] = f[0][x];
                    q.push(Node(x,dis[1][x],true));
                }
                dis[0][x] = gx;f[0][x] = f[o][v];
                q.push(Node(x,dis[0][x],false));
            }
            else if(gx == dis[0][x])
                f[0][x] += f[o][v];
            else if(gx == dis[1][x])
                f[1][x] += f[o][v];
            else if(gx < dis[1][x]){
                dis[1][x] = gx;f[1][x] = f[o][v];
                q.push(Node(x,dis[1][x],true));
            }
        }
    }
}

inline void clear(){
    FOR(i,1,n) head[i] = 0;cnt = 0;CLR(vis,0);
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);
    }
    scanf("%d%d",&S,&T);dij();
    int ans = f[0][T] + (dis[0][T]+1 == dis[1][T] ? f[1][T] : 0);
    printf("%d\n",ans);clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

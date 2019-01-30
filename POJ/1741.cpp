#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000+6;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],size[MAXN],max[MAXN],min,n,K;
bool vis[MAXN];
std::vector<int> dis;
int cnt,ans,root;

inline void init(){
    cnt = ans = 0;size[1] = n;
    CLR(head,0);CLR(vis,false);
}

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

void findroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int i = head[v];i;i = e[i].next){
        int to = e[i].to;
        if(vis[to] || to == fa) continue;
        findroot(to,v);
        size[v] += size[to];
        max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],n-size[v]);
    if(min > max[v]){
        min = max[v];
        root = v;
    }
}

inline void findist(int v,int fa,int w){
    dis.push_back(w);
    for(int i = head[v];i;i = e[i].next){
        int to = e[i].to;
        if(!vis[to] && to != fa) findist(to,v,w+e[i].w);
    }
}

inline int calc(int v,int w){
    dis.clear();int res = 0;
    findist(v,0,w);std::sort(dis.begin(),dis.end());
    int i = 0,j = dis.size()-1;
    while(i < j){
        while(dis[i] + dis[j] > K && i < j) j--;
        res += j-i++;
    }
    return res;
}

void dfs(int v){
    min = n = size[v];findroot(v,0);
    ans += calc(root,0);vis[root] = 1;
    for(int i = head[root];i;i = e[i].next){
        int to = e[i].to;
        if(!vis[to]){
            ans -= calc(to,e[i].w);
            dfs(to);
        }
    }
}

int main(){
    while(~scanf("%d%d",&n,&K)){
        if(!n && !K) break;
        init();
        FOR(i,1,n-1){
            int u,v,w;scanf("%d%d%d",&u,&v,&w);
            add(u,v,w);add(v,u,w);
        }
        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}
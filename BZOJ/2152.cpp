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

const int MAXN = 20000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],size[MAXN],max[MAXN],dis[MAXN],t[100];
int root,sum,N,cnt;
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline void getroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)] || to == fa) continue;
        getroot(to,v);size[v] += size[to];
        max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],sum-size[v]);
    root = max[root] > max[v] ? v : root;
}

inline void getdis(int v,int fa){
    t[dis[v]]++;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        dis[to] = (dis[v] + e[i].w)%3;
        getdis(to,v);
    }
}

inline int calc(int v,int val){
    CLR(t,0);dis[v] = val;getdis(v,0);
    return t[1]*t[2]*2+t[0]*t[0];
}

int ans;

inline void divide(int v){
    ans += calc(v,0);vis[v] = true;
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        ans -= calc(to,e[i].w);sum = size[to];max[root = 0] = INT_MAX;
        getroot(to,0);divide(root);
    }
}

inline int gcd(int x,int y){
    return (!y) ? x : gcd(y,x%y);
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);w %= 3;
        add(u,v,w);add(v,u,w);
    }
    sum = max[root=0] = N;getroot(1,0);divide(root);
    int k = gcd(ans,N*N);
    printf("%d/%d\n",ans/k,N*N/k);
    return 0;
}
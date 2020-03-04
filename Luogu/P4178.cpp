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

const int MAXN = 40000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int head[MAXN],dis[MAXN],size[MAXN],max[MAXN],cnt,root,sum;
bool vis[MAXN];
int N,K,st[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

void getroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        getroot(to,v);size[v] += size[to];
        max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],sum-max[v]);
    root = max[root] > max[v] ? v : root;
}

void getdis(int v,int fa){
    st[++st[0]] = dis[v];
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        dis[to] = dis[v] + e[i].w;getdis(to,v);
    }
}

int calc(int v,int val){
    int res = 0;
    st[0] = 0;dis[v] = val;
    getdis(v,0);std::sort(st+1,st+st[0]+1);
    for(int l = 1,r = st[0];l < r;){
        if(st[l] + st[r] <= K) res += r-l++;
        else --r;
    }
    return res;
}

int ans = 0;

void divide(int v){
    ans += calc(v,0);vis[v] = true;
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        ans -= calc(to,e[i].w);
        max[root = 0] = sum = size[to];
        getroot(to,0);divide(root);
    }
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    scanf("%d",&K);
    max[root = 0] = sum = N;getroot(1,0);
    divide(root);
    printf("%d\n",ans);
    return 0;
}
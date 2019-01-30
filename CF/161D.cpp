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

const int MAXN = 50000+5;
const int MAXK = 500+5;

struct Edge{
    int to,next;
}e[MAXN<<1];
int head[MAXN],size[MAXN],max[MAXN],dis[MAXN],cnt;
int root,N,sum,K;
bool vis[MAXN];
int p[MAXN],st[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

inline void getroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        getroot(to,v);size[v] += size[to];
        max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],sum-size[v]);
    root = max[root] > max[v] ? v : root;
}

inline void getdis(int v,int fa){
    st[++st[0]] = dis[v];p[dis[v]]++;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        dis[to] = dis[v] + 1;getdis(to,v);
    }
}
LL ans = 0;
inline int calc(int v,int val){
    st[0] = 0;dis[v] = val;
    getdis(v,0);int res = 0;
    FOR(i,1,st[0]){
        if(K >= st[i]) res += (st[i]*2 != K) ? 1ll*p[st[i]]*p[K-st[i]] : 1ll*p[st[i]]*(p[st[i]]-1)/2;
        p[st[i]] = 0;
        if(K >= st[i]) p[K-st[i]] = 0;
    }
    return res;
}

inline void divide(int v){
    ans += calc(v,0);vis[v] = 1;
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        ans -= calc(to,1);max[root=0]=INT_MAX;sum = size[to];
        getroot(to,0);divide(root);
    }
}

int main(){
    scanf("%d%d",&N,&K);max[root=0] = sum = N;
    FOR(i,1,N-1){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
    getroot(1,0);
    divide(root);
    printf("%I64d\n",ans);
    return 0;
}
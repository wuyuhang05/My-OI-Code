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
#define DEBUG(x) std::cerr << #x << '=' << x << std::

const int MAXN = 100000+5;
const int MAXK = 10000000+2;

struct Edge{
    int to,w,next;
}e[MAXN<<1];
int N,M;
int head[MAXN],cnt;
int query[MAXN],size[MAXN],max[MAXN],dis[MAXN],q[MAXN];
int st[MAXN];
bool vis[MAXN],test[MAXK],p[MAXK];
int root,sum;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline void getroot(int v,int fa){
    size[v] = 1;max[v] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        getroot(to,v);
        size[v] += size[to];max[v] = std::max(max[v],size[to]);
    }
    max[v] = std::max(max[v],sum-size[v]);
    if(max[root] > max[v]) root = v;
}

void getdis(int v,int fa){
    st[++st[0]] = dis[v];
    for(int to,i = head[v];i;i = e[i].next){
        if((to = e[i].to) == fa || vis[to]) continue;
        dis[to] = dis[v] + e[i].w;
        getdis(to,v);
    }
}

void calc(int v){
    q[0] = 0;
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        st[0] = 0;dis[to] = e[i].w;getdis(to,v);
        FOR(j,1,st[0])
            FOR(k,1,M)
                if(query[k] >= st[j])
                    test[k] |= p[query[k] - st[j]];
        FOR(j,1,st[0]){
            q[++q[0]] = st[j];p[st[j]] = true;
        }
    }
    FOR(i,1,q[0]) p[q[i]] = 0;
}

void divide(int v){
    vis[v] = p[0] = true;calc(v);
    for(int to,i = head[v];i;i = e[i].next){
        if(vis[(to = e[i].to)]) continue;
        sum = size[to];max[root=0]=INT_MAX;
        getroot(to,0);divide(root);
    }
}

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    FOR(i,1,M) scanf("%d",query+i);
    max[root=0] = sum = N;getroot(1,0);
    divide(root);
    FOR(i,1,M){
        puts(test[i] ? "AYE" : "NAY");
    }
    return 0;
}
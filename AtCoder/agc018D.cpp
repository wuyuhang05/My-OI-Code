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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];

int head[MAXN],cnt,size[MAXN],max[MAXN];
int N;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

void dfs(int v,int fa){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        size[v] += size[e[i].to];
        max[v] = std::max(max[v],size[e[i].to]);
    }
    max[v] = std::max(max[v],N-size[v]);
}

LL ans;

void dfs(int v,int fa,LL val){
    size[v] = 1;
    for(int i = head[v];i;i = e[i].next){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v,val+e[i].w);
        size[v] += size[e[i].to];
    }
    ans += val;
}

int main(){
    scanf("%d",&N);
    FOR(i,1,N-1){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    dfs(1,0);int s=0;
    FOR(i,1,N) if(2*max[i] <= N) s = i;
    dfs(s,0,0ll);int min=INT_MAX;
    for(int i = head[s];i;i = e[i].next){
        if(size[e[i].to] == (N+1)/2){
            min = e[i].w;break;
        }
        else min = std::min(min,e[i].w);
    }
    printf("%lld\n",2*ans-min);
    return 0;
}
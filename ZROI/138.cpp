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

const int MAXN = 1000+5;

struct Edge{
    int to,w,next;
}e[MAXN<<1];

int head[MAXN],cnt,ans;
int d[MAXN],x[MAXN],y[MAXN],a[MAXN],b[MAXN];
bool vis[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    d[v]++;
}

void dfs(int v){
    for(int id,i = head[v];i;i = e[i].next){
        if(!vis[id = e[i].w]){
            vis[id] = true;
            a[id] = v;b[id] = e[i].to;
            dfs(e[i].to);
        }
    }
}

int N,M;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,M){
        scanf("%d%d",x+i,y+i);
        add(x[i],y[i],i);add(y[i],x[i],i);
    }
    FOR(i,1,N){
        if(d[i] & 1) add(i,N+1,++M),add(N+1,i,M);
        else ans++;
    }
    printf("%d\n",ans);
    FOR(i,1,N) dfs(i);
    for(int i = 1;i <= M && x[i];++i) printf("%d",!(x[i] == a[i]));
    puts("");
    return 0;
}
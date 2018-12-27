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

const int MAXN = 300+5;
const int MAXM = 400+5;

struct Edge{
    int to,next;
}e[MAXM<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int N,M,K,ans;
bool vis[MAXN];
int f[MAXN],pre[MAXN];
int q[6][MAXN];

inline void init(){
    cnt = 0;CLR(head,0);CLR(vis,0);
    CLR(f,0);CLR(pre,0);CLR(q,0);
}

void dfs(int step){
    int max=0;
    ROF(v,N,1){
        if(!vis[v]){
            f[v] = 1;pre[v] = 0;
            for(int t,i = head[v];i;i = e[i].next){
                t = e[i].to;
                if(!vis[t]){
                    if(f[v] < f[t] + 1) f[v] = f[t]+1,pre[v] = t;
                }
            }
            if(f[v] > f[max]) max = v;
            if(step > K && f[max] > ans) return;
        }
    }
    ans = std::min(ans,f[max]);
    if(step > K) return;
    int top = 0;
    for(int i = max;i;i = pre[i]) q[step][++top] = i;
    FOR(i,1,top){
        if(step+1 <= K || i <= ans && top-i+1 <= ans){
            vis[q[step][i]] = 1;
            dfs(step+1);
            vis[q[step][i]] = 0;
        }
    }
}

inline void Solve(){
    init();scanf("%d%d%d",&N,&M,&K);
    ans = N;
    FOR(i,1,M){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }dfs(1);
    printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
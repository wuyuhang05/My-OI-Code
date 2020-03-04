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

const int MAXN = 100;
const int MAXM = 20000+5;

struct Edge{
    int u,v,w;
}e[MAXM<<1];
int N,M,root,cnt,ans;
int in[MAXN],vis[MAXN],id[MAXN],pre[MAXN];

int main(){
    scanf("%d%d%d",&N,&M,&root);
    FOR(i,1,M) scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    while("SDOI 2018 AK"){
        cnt = 0;
        FOR(i,1,N) in[i] = INT_MAX,vis[i] = id[i] = 0;
        FOR(i,1,M){
            if(e[i].u != e[i].v && e[i].w < in[e[i].v]){
                in[e[i].v] = e[i].w;
                pre[e[i].v] = e[i].u;
            }
        }
        in[root] = 0;
        FOR(i,1,N){
            if(in[i] == INT_MAX){
                printf("%d\n",-1);
                return 0;
            }
            ans += in[i];int u;
            for(u = i;u != root && vis[u] != i && !id[u];u = pre[u]) vis[u] = i;
            if(u != root && !id[u]){
                id[u] = ++cnt;
                for(int v = pre[u];v != u;v = pre[v]) id[v] = cnt;
            }
        }
        if(!cnt){
            printf("%d\n",ans);
            return 0;
        }
        FOR(i,1,N) if(!id[i]) id[i] = ++cnt;
        FOR(i,1,M){
            int t = in[e[i].v];
            if((e[i].u = id[e[i].u]) != (e[i].v = id[e[i].v])){
                e[i].w -= t;
            }
        }
        N = cnt;root = id[root];
    }
    return 0;
}
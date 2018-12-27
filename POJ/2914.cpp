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
int f[MAXN][MAXN],dist[MAXN];
bool vis[MAXN],del[MAXN];
int N,M;

inline void init(){
    CLR(f,0);CLR(del,false);
}

int contract(int &s,int &t){
    int min=0;
    CLR(dist,0);CLR(vis,0);
    FOR(i,1,N){
        int k = -1,max = -1;
        FOR(j,1,N){
            if(!del[j] && !vis[j] && dist[j] > max){
                k = j;max = dist[j];
            }
        }
        if(k == -1) return min;
        s = t,t = k;
        min = max;
        vis[k] = true;
        FOR(j,1,N){
            if(!del[j] && !vis[j]) dist[j] += f[k][j];
        }
    }
    return min;
}

int SW(){
    int min = INT_MAX;
    FOR(i,1,N-1){
        int s,t;
        min = std::min(min,contract(s,t));
        del[t] = true;
        if(min == 0) return 0;
        FOR(j,1,N) if(!del[j]) f[s][j] = (f[j][s] += f[j][t]);
    }
    return min;
}

inline void Solve(){
    init();
    FOR(i,1,M){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        u++;v++;
        f[u][v] = (f[v][u] += w);
    }
    printf("%d\n",SW());
}

int main(){
    while(~scanf("%d%d",&N,&M)) Solve();
    return 0;
}
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 12000+5;

struct Edge{
    int to,c,next;
}e[MAXN*10];

int head[MAXN],cur[MAXN],level[MAXN],cnt = 1;

inline void add(int u,int v,int c){
    e[++cnt] = (Edge){v,c,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
}

int N,S,T;

inline bool bfs(){
    FOR(i,0,N) level[i] = 0,cur[i] = head[i];
    std::queue<int> q;q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();//DEBUG(v);
        for(int i = head[v];i;i = e[i].next){
            if(!level[e[i].to] && e[i].c > 0){
                level[e[i].to] = level[v] + 1;
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int limit=INT_MAX){
    if(v == T) return limit;
    int flow;
    for(int &i = cur[v];i;i = e[i].next){
        if(e[i].c > 0 && level[e[i].to] == level[v] + 1){
            if((flow = dfs(e[i].to,std::min(limit,e[i].c)))){
                e[i].c -= flow;
                e[i^1].c += flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int dinic(){
    int res = 0,flow;
    while(bfs()){
        while((flow = dfs(S))) res += flow;
    }
    return res;
}

int n,m,k;
int type[MAXN];

int main(){
    scanf("%d%d%d",&n,&m,&k);
    S = 0;N = T = n+(m<<1)+1;// DEBUG(S);DEBUG(T);
    FOR(i,1,n) scanf("%d",type+i);
    FOR(i,1,n){
        if(type[i]) add(i+(m<<1),T,1);
        else add(S,i+(m<<1),1);
    }
    FOR(i,1,m) add(i<<1,(i<<1)-1,1);
    FOR(i,1,k){
        int u,v;scanf("%d%d",&u,&v);
        if(type[u]) add((v<<1)-1,u+(m<<1),1);
        else add(u+(m<<1),v<<1,1);
    }
    printf("%d\n",dinic());
    return 0;
}

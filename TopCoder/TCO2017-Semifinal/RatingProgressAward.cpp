/*
 * Author: RainAir
 * Time: 2019-08-01 20:02:30
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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

const int MAXN = 200+5;
const int MAXM = MAXN*MAXN+2;

struct Edge{
    int to,nxt,cap,flow;
}e[MAXM];
int head[MAXN],cur[MAXN],level[MAXN],cnt = 1;
int S,T,N;

inline void add(int u,int v,int w){
    if(!w) return;
    w = std::abs(w);//printf("%d %d %d\n",u,v,w);
    e[++cnt] = (Edge){v,head[u],w,0};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

inline bool bfs(){
    std::queue<int> q;
    FOR(i,0,N) level[i] = 0,cur[i] = head[i];
    q.push(S);level[S] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(!level[e[i].to] && e[i].cap > e[i].flow){
                level[e[i].to] = level[v] + 1;
              //  DEBUG(e[i].to);
                if(e[i].to == T) return true;
                q.push(e[i].to);
            }
        }
    }
    return false;
}

inline int dfs(int v,int lim = INT_MAX){
    if(!lim) return 0;
    if(v == T) return lim;int flow;
    for(int &i = cur[v];i;i = e[i].nxt){
        if(e[i].cap > e[i].flow && level[e[i].to] == level[v] + 1){
            if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
                e[i].flow += flow;
                e[i^1].flow -= flow;
                return flow;
            }
        }
    }
    return 0;
}

inline int Dinic(){
    int ans = 0,flow;
    while(bfs()){
        while((flow = dfs(S))) ans += flow;
    }
    return ans;
}

class RatingProgressAward{
public:
    int n,m;
    int maximalProgress(std::vector<int> change,std::vector<int> a,std::vector<int> b){
        n = change.size();m = a.size();
        S = 0,T = 2*n+1;N = T;int sm = 0;
        FOR(i,1,n){
            if(change[i-1] > 0) sm += change[i-1];
            add(S,i,std::max(0,change[i-1]));
            add(i,i+n,std::min(0,change[i-1]));
            add(i+n,i,INT_MAX);
            add(i+n,T,std::max(0,change[i-1]));
        }
        FOR(i,1,m){
            add(b[i-1]+1,a[i-1]+1,INT_MAX);
            add(b[i-1]+1+n,a[i-1]+1+n,INT_MAX);
        }
        return sm-Dinic();
    }
};
/*
int main(){
    RatingProgressAward work;
    int n,m;scanf("%d%d",&n,&m);
    std::vector<int> change,a,b;int x;
    FOR(i,1,n) scanf("%d",&x),change.pb(x);
    FOR(i,1,m) scanf("%d",&x),a.pb(x);
    FOR(i,1,m) scanf("%d",&x),b.pb(x);
    printf("%d\n",work.maximalProgress(change,a,b));
    return 0;
}*/

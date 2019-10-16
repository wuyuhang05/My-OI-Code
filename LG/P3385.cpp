/*
 * Author: RainAir
 * Time: 2019-10-11 16:14:20
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;
const int MAXM = 3000+5;

int n,m;

struct Edge{
    int to,w,nxt;
}e[MAXM<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int dis[MAXN],t[MAXN];
bool inq[MAXN];

inline bool spfa(){
    std::queue<int> q;
    FOR(i,1,n) dis[i] = 1e9,t[i] = inq[i] = 0;
    dis[1] = 0;q.push(1);inq[1] = true;
    while(!q.empty()){
        int v = q.front();q.pop();inq[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                if(++t[e[i].to] > n) return true;
                if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = true;
            }
        }
    }
    return false;
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        if(w >= 0) add(u,v,w),add(v,u,w);
        else add(u,v,w);
    }
    puts(spfa() ? "YE5" : "N0");
    cnt = 0;FOR(i,1,n) head[i] = 0;
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

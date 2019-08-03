/*
 * Author: RainAir
 * Time: 2019-08-01 19:13:49
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
#define P std::pair<LL,int>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 500000+5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<2];
int cnt,head[MAXN];
LL dis[MAXN];bool used[MAXN];

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int S,T,N,n;

inline void dij(){
    FOR(i,0,MAXN-1) dis[i] = 1e18;
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;q.push(MP(dis[S] = 0,S));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}

int main(){
    scanf("%d",&n);
    S = 1,T = n*n+2;
    FOR(i,0,n){
        FOR(j,1,n){
            int x;scanf("%d",&x);
            if(!i) add(1+j,T,x);
            else if(i == n) add(S,1+(i-1)*n+j,x);
            else add(1+i*n+j,1+(i-1)*n+j,x);
        }
    }
    FOR(i,1,n){
        FOR(j,0,n){
            int x;scanf("%d",&x);
            if(!j) add(S,1+(i-1)*n+1,x);
            else if(j == n) add(1+i*n,T,x);
            else add(1+(i-1)*n+j,1+(i-1)*n+j+1,x);
        }
    }
    FOR(i,0,n){
        FOR(j,1,n){
            int x;scanf("%d",&x);
            if(!i) add(T,1+j,x);
            else if(i == n) add(1+(i-1)*n+j,S,x);
            else add(1+(i-1)*n+j,1+i*n+j,x);
        }
    }
    FOR(i,1,n){
        FOR(j,0,n){
            int x;scanf("%d",&x);
            if(!j) add(1+(i-1)*n+1,S,x);
            else if(j == n) add(T,1+i*n,x);
            else add(1+(i-1)*n+j+1,1+(i-1)*n+j,x);
        }
    }
    dij();
    printf("%lld\n",dis[T]);
    return 0;
}

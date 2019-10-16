/*
 * Author: RainAir
 * Time: 2019-10-12 07:47:19
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

const int MAXN = 1e5 + 5;
int n,k;

struct Edge{
    int to,w,nxt;
}e[MAXN<<3];
int head[MAXN],cnt,S;

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

LL dis[MAXN];
int d[MAXN];
bool inq[MAXN];

inline void spfa(){
    FOR(i,1,n) dis[i] = -1e18;
    std::queue<int> q;q.push(S);inq[S] = true;
    while(!q.empty()){
        int v = q.front();q.pop();inq[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] < dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                if(++d[e[i].to] > n+1){
                    puts("-1");
                    exit(0);
                }
                if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = true;
            }
        }
    }
    LL ans = 0;
    FOR(i,1,n) ans += dis[i];
    printf("%lld\n",ans);exit(0);
}

int main(){
    scanf("%d%d",&n,&k);
    S = n+1;
    FOR(i,1,k){
        int opt,u,v;scanf("%d%d%d",&opt,&u,&v);
        if(opt == 1){ // a <= b,b <= a
            add(u,v,0);
            add(v,u,0);
        }
        if(opt == 2){ // a+1 <= b
            if(u == v){
                puts("-1");
                return 0;
            }
            add(u,v,1);
        }
        if(opt == 3){ // b <= a
            add(v,u,0);
        }
        if(opt == 4){ // b+1 <= a
            add(v,u,1);
            if(u == v){
                puts("-1");
                return 0;
            }
        }
        if(opt == 5){ // a <= b
            add(u,v,0);
        }
    }
    FOR(i,1,n) add(S,i,1);
    //ROF(i,n,1) add(S,i,1);
    spfa();
    return 0;
}

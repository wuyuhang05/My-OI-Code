/*
 * Author: RainAir
 * Time: 2019-10-31 16:50:17
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

const int MAXN = 1e6 + 5;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],ccnt,n,m,ru[MAXN];

inline void add(int u,int v){
    e[++ccnt] = (Edge){v,head[u]};head[u] = ccnt;
    ++ru[v];
}

inline int calc(int u,int t){
    return u+t*n;
}

int du[MAXN];
int f[MAXN],cnt[MAXN];

inline void bfs(){
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) f[calc(i,0)] = f[calc(i,1)] = 0,q.push(calc(i,0)),q.push(calc(i,1));
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(v > n){
                ++cnt[e[i].to];
                if(cnt[e[i].to] == ru[e[i].to]) f[e[i].to] = f[v]+1,q.push(e[i].to);
            }
            else{
                ++cnt[e[i].to];
                if(cnt[e[i].to] == 1) f[e[i].to] = f[v] + 1,q.push(e[i].to);
            }
        }
    }
}

int main(){
    freopen("idioms.in","r",stdin);
    freopen("idioms.out","w",stdout);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);
        add(calc(v,0),calc(u,1));
        add(calc(v,1),calc(u,0));
        du[u]++;
    }
    FOR(i,1,n*2) f[i] = 1e9;
    bfs();
    FOR(i,1,n) printf("%d\n",f[i+n] == 1e9 ? -1 : f[i+n]);
    return 0;
}

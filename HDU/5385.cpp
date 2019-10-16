/*
 * Author: RainAir
 * Time: 2019-08-29 15:37:59
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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3e5 + 5;
const int MAXM = 6e5 + 5;

struct Edge{
    int to,nxt;
}e[MAXM];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dis[MAXN],fa[MAXN],ts;

inline void addtag(int v){
    for(int i = head[v];i;i = e[i].nxt){
        if(!fa[e[i].to]) fa[e[i].to] = v;
    }
}

int n,m;
P edge[MAXN];

inline void clear(){
    FOR(i,1,m) edge[i].fi = edge[i].se = 0;
    cnt = 0;FOR(i,1,n) head[i] = dis[i] = fa[i] = 0;ts = 0;
}

inline void Solve(){
    fa[1] = -1;ts = 0;
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        scanf("%d%d",&edge[i].fi,&edge[i].se);
        add(edge[i].fi,edge[i].se);
    }
    int l = 1,r = n;
    while(l <= r){
        if(fa[l]){
            addtag(l);
            dis[l++] = ++ts;
        }
        if(fa[r]){
            addtag(r);
            dis[r--] = ++ts;
        }
    }
    FOR(i,1,m){
        if(fa[edge[i].se] != edge[i].fi) printf("%d\n",n);
        else printf("%d\n",dis[edge[i].se]-dis[edge[i].fi]);
    }
    clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

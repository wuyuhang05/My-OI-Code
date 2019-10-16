/*
 * Author: RainAir
 * Time: 2019-09-17 14:53:12
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
#define int LL
const int MAXN = 2e5 + 5;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];

int n,m,q,head[MAXN],du[MAXN],cnt;
std::vector<int> a[MAXN],t;

inline void add(int u,int v,int w){
    du[v]++;
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
//    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

inline void merge(int x,int y,int w){ // (x->y) = w
    if(a[x].empty()) return;int i,j;
    for(i = j = 1;i < a[x].size() && j < a[y].size();) 
        t.pb(a[x][i]+w < a[y][j] ? a[x][i++]+w : a[y][j++]);
    while(i < a[x].size()) t.pb(a[x][i++]+w);
    while(j < a[y].size()) t.pb(a[y][j++]);
    a[y].clear();
    a[y].pb(-1e18);a[y].pb(t[0]);
    FOR(i,1,(int)t.size()-1){
        int x = t[i];
        int sz = (int)a[y].size()-1; // tail
        if(a[y][sz-1]+a[y][sz-1]/10 >= x) a[y][sz] = x;// (a[y][sz-1] >= x/1.1)
        else a[y].pb(x);
    }
    t.clear();
}
// 一个数x对答案的贡献是 [x/1.1,x] 
// x >= y 新来一个数 z z/1.1 <= x <= y <= z 可以删除 y

inline void topsort(){
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) q.push(i);
    //FOR(i,1,n) a[i].pb(-1e9);
    a[1].pb(-1e18);a[1].pb(0);
    while(!q.empty()){
        int v = q.front();q.pop();
//        DEBUG(a[v].size());
        for(int i = head[v];i;i = e[i].nxt){
            merge(v,e[i].to,e[i].w);
            if(!--du[e[i].to]) q.push(e[i].to);
        }
    }
}

signed main(){
   // freopen("a.in","r",stdin);
  //  freopen("a.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&q);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    topsort();
    FOR(i,1,n) a[i].pb(1e18);
    int mx = 0;FOR(i,1,n) mx = std::max(mx,(int)(a[i].size()));
    //DEBUG(mx);
    FOR(i,1,q){
        int k,d;scanf("%lld%lld",&k,&d);
        int ps = std::lower_bound(all(a[k]),d) - a[k].begin();
        puts(a[k][ps] <= 1.1*d ? "YES" : "NO");
    }
    return 0;
}

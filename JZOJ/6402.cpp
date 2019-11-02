/*
 * Author: RainAir
 * Time: 2019-11-02 15:28:18
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

const int MAXN = 3e5 + 5;
int n;

struct Node{
    int l,r,w;
    bool operator < (const Node &t) const {
        return l == t.l ? r > t.r : l < t.l;
    }
}a[MAXN];

int f[MAXN],rt;

inline int find(int x){
    int i;
    for(i = x+1;i <= n && a[i].r <= a[x].r;){
        if(f[i]){
            ++i;
            continue;
        }
        f[i] = x;
        i = find(i);
    }
    return i;
}

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dep[MAXN],son[MAXN];

inline void dfs1(int v){
    dep[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        dfs1(e[i].to);
        if(dep[son[v]] < dep[e[i].to]) son[v] = e[i].to;
        dep[v] = std::max(dep[v],dep[e[i].to]+1);
    }
    if(!son[v]) son[v] = v;
}

std::multiset<LL,std::greater<LL> > g[MAXN];
// g[i][j] = f[i][j] - f[i][j-1]
LL tmp[MAXN];

inline void dfs2(int v){
    for(int i = head[v];i;i = e[i].nxt) dfs2(e[i].to);
    int t = son[v];
    son[v] = son[son[v]];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == t) continue;
        int cnt = 0,sz = 0;
        for(auto x:g[son[e[i].to]]){
            tmp[++cnt] = x;
        }
        sz = cnt;
        cnt = 0;
        for(auto x:g[son[v]]){
            tmp[++cnt] += x;
            if(cnt == sz) break;
        }
        FOR(i,1,sz) g[son[v]].erase(g[son[v]].begin());
        FOR(i,1,sz) g[son[v]].insert(tmp[i]);
    }
    if(v != rt) g[son[v]].insert(a[v].w);
}

int main(){
    freopen("cover10.in","r",stdin);
    freopen("cover.out","w",stdout);
    scanf("%*d%d",&n);
    rt = n+1;
    FOR(i,1,n) scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].w);
    std::sort(a+1,a+n+1);
    FOR(i,1,n) if(!f[i]) f[i] = rt,find(i);
    FOR(i,1,n) add(f[i],i);
    dfs1(rt);
    dfs2(rt);
    int cnt = 0;
    for(auto x:g[son[rt]]) tmp[++cnt] = x;
    FOR(i,2,n) tmp[i] += tmp[i-1];
    FOR(i,1,n) printf("%lld ",tmp[i]);
    puts("");
    return 0;
}

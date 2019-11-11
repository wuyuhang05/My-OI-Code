/*
 * Time: 2019-11-11 14:56:17
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

const int MAXN = 5e6 + 5;
const LL ha = 2148473648;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

std::vector<int> TP[MAXN];
int son[MAXN],bel[MAXN],mxd[MAXN],dep[MAXN];
int fa[MAXN];
/*
inline void dfs1(int v,int fa=0){
    mxd[v] = dep[v];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dep[e[i].to] = dep[v] + 1;
        dfs1(e[i].to,v);
        mxd[v] = std::max(mxd[v],mxd[e[i].to]);
        if(mxd[son[v]] < mxd[e[i].to]) son[v] = e[i].to;
    }
}
*/
int n,m,s,l;
inline void dfs1(){
    std::queue<int> q;q.push(1);
    dep[1] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        TP[dep[v]].pb(v);
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa[v]) continue;
            dep[e[i].to] = dep[v] + 1;
            fa[e[i].to] = v;
            q.push(e[i].to);
        }
    }
    ROF(i,n,1){
        if(TP[i].empty()) continue;
        for(auto x:TP[i]){
            mxd[x] = std::max(mxd[x],dep[x]);
            mxd[fa[x]] = std::max(mxd[fa[x]],mxd[x]);
            if(mxd[son[fa[x]]] < mxd[x]) son[fa[x]] = x;
        }
    }
}
/*
inline void dfs2(int v,int fa=0,int tp=0){
    bel[v] = tp;
    if(son[v]) dfs2(son[v],v,tp);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to != fa && e[i].to != son[v])
            dfs2(e[i].to,v,e[i].to);
    }
}*/

inline void dfs2(){
    std::queue<P> q;q.push(MP(1,1));
    while(!q.empty()){
        int v = q.front().fi;bel[v] = q.front().se;q.pop();
        if(son[v]) q.push(MP(son[v],bel[v]));
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to != fa[v] && e[i].to != son[v]) q.push(MP(e[i].to,e[i].to));
        }
    }
}

P q[MAXN];
int ans[MAXN];
int f[MAXN],val[MAXN],p = 0;
// f: >=i 的个数
//  g: =i 的个数
//   h >=i 的 sum
int now = 0;
inline int move(int ps){
    if(ps+1 > p+1) now++;
    else if(ps+1 == p+1) now += p+1;
    f[ps+1]++;
    bool ed = false;
    while(f[p+1] >= l){
        if(ed) now -= (f[p+1]-f[p])*p;
        p++;ed = true;
    }
    if(ed) now -= (f[p]-f[p+1])*p;
    int t = l-f[p+1];
    return now+t*p;
}

int qqq[MAXN];

int main(){
    freopen("a.in","r",stdin);
  //  freopen("tour.out","w",stdout);
    scanf("%d%d%d",&n,&m,&l);
    FOR(i,2,n){
        int f;scanf("%d",&f);
        add(f,i);
    }
    dep[1] = 1;
    dfs1();dfs2();
    ans[0] = 0;ans[1] = 1;val[1] = 1;f[0] = n;f[1] = 1;
    now = 1;
    FOR(i,2,n){
  //      DEBUG(i);puts("");
        int t = now;
        if(TP[i].empty()){
            ans[i] = ans[i-1];
            continue;
        }
        for(auto x:TP[i]){
            t = move(val[bel[x]]);
            val[bel[x]]++;
        }
        ans[i] = t;
    }
    FOR(i,1,m){
        int d;scanf("%d",&d);
        qqq[i] = d;
    }
    LL anss = 0;
    ROF(i,m,1) anss = (1ll*anss*233%ha+ans[qqq[i]+1])%ha;
    anss = 1ll*anss*233%ha;
    printf("%lld\n",anss);
    return 0;
}

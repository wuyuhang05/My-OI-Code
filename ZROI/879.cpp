/*
 * Author: RainAir
 * Time: 2019-08-05 19:35:38
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
#define int LL
const int MAXN = 2e5 + 5;
int a[MAXN];
namespace Tree{
    struct Edge{
        int to,w,nxt,id;  
    }e[MAXN<<1];
    int cnt = 0;int head[MAXN];

    inline void add(int u,int v,int w,int id){
        e[++cnt] = (Edge){v,w,head[u],id};head[u] = cnt;
        e[++cnt] = (Edge){u,w,head[v],id};head[v] = cnt;
    }

    std::vector<int> ans;
    int sm[MAXN];
    
    inline void dfs(int v,int fa=0){
        sm[v] = a[v];
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dfs(e[i].to,v);sm[v] += sm[e[i].to]-e[i].w;
        }
    }

    inline void work(int v,int fa=0){
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            if(sm[e[i].to]-e[i].w >= 0){
                if(sm[e[i].to] >= 0) work(e[i].to,v),ans.pb(e[i].id);
                else ans.pb(e[i].id),work(e[i].to,v);
            }
        }
        //DEBUG(v);
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            if(sm[e[i].to]-e[i].w < 0){
                if(sm[e[i].to] >= 0) work(e[i].to,v),ans.pb(e[i].id);
                else ans.pb(e[i].id),work(e[i].to,v);
            }
        }
    }

    inline void Solve(){
        dfs(1);work(1);
        for(auto x:ans) printf("%lld ",x);
        puts("");exit(0);
    }
};
struct Edge{
    int u,v,w,id;
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXN],e2[MAXN];
int n,m;
int f[MAXN];

inline int find(int x){
    return x == f[x] ? x : f[x] = find(f[x]);
}

inline void Kruskal(){
    FOR(i,1,n) f[i] = i;int cnt=0,sum = 0;
    FOR(i,1,m){
        int u = e[i].u,v = e[i].v,w = e[i].w;
        int fu = find(u),fv = find(v);
        if(fu == fv) continue;
        e2[++cnt] = e[i];sum += w;
        f[fu] = fv;
        if(cnt == n-1) break;
    }
    int ds = 0;FOR(i,1,n) ds += a[i];
    if(ds < sum){
        puts("0");exit(0);
    }
}

signed main(){
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,m) scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w),e[i].id = i;
    std::sort(e+1,e+m+1);Kruskal();
    FOR(i,1,n-1){
        int u = e2[i].u,v = e2[i].v,w = e2[i].w,id = e2[i].id;
        Tree::add(u,v,w,id);
    }
    puts("1");
    Tree::Solve();
    return 0;
}

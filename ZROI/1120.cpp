/*
 * Author: RainAir
 * Time: 2019-10-01 09:49:08
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
#define int LL
const int MAXN = 2e5 + 5;
const int MAXM = 20;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,m;

inline void add(int u,int v,int w=19260817){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int sm = 0;

namespace Part1{
//public:
    int f[MAXN][MAXM+1],dep[MAXN],cf[MAXN];
    P bian[MAXN];

    inline void dfs(int v,int fa=0){
        f[v][0] = fa;
        FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dep[e[i].to] = dep[v] + 1;dfs(e[i].to,v);
        }
    }

    inline int lca(int x,int y){
        if(dep[x] != dep[y]){
            if(dep[x] < dep[y]) std::swap(x,y);
            int d = dep[x] - dep[y];
            FOR(i,0,20) if((1<<i)&d) x = f[x][i];
        }
        if(x == y) return x;
        ROF(i,20,0){
            if(f[x][i] == f[y][i]) continue;
            x = f[x][i],y = f[y][i];
        }
        return f[x][0];
    }

    inline void dfss(int v,int fa=0){
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            dfss(e[i].to,v);cf[v] += cf[e[i].to];
            bian[e[i].to] = MP(v,e[i].to);//dfs(e[i].to,v);
        }
    }

    inline void Solve(){
        dfs(1);
        FOR(i,1,m){
            int x,y;scanf("%lld%lld",&x,&y);
            int l = lca(x,y);
            cf[l] -= 2;cf[x]++;cf[y]++;
        }
        dfss(1);
        cnt = 0;CLR(head,0);
        FOR(i,2,n) add(bian[i].fi,bian[i].se,cf[i]);//,DEBUG(cf[i]);
        FOR(i,2,n) sm += cf[i];
    }
};

namespace Part2{
//public:
    int ans = -1;
    int now = 0;
    int mn[MAXN],cmn[MAXN];

    inline void dfs(int v,int fa=0){
        mn[v] = 0;cmn[v] = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            if(e[i].w > mn[v]) cmn[v] = mn[v],mn[v] = e[i].w;
            else if(e[i].w > cmn[v]) cmn[v] = e[i].w;
            dfs(e[i].to,v);
        }
        if(mn[v] != 0) now += mn[v];
    }

    inline int relax(int v,int ban){
        int mx = 0;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == ban) continue;
            mx = std::max(mx,e[i].w);
        }
        return mx;
    }

    inline void dfss(int v,int fa=0,int fw = 0){
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == fa) continue;
            int t = now;
            P t1 = MP(mn[v],cmn[v]);
            P t2 = MP(mn[e[i].to],cmn[e[i].to]);
            //if(v == 7 && e[i].to == 8) DEBUG(now);
            //if(v == 1 && e[i].to == 2) DEBUG(now);
            if(e[i].w == mn[v]){
                now = now-mn[v];
                if(cmn[v] != -1) now += cmn[v];
             //   if(v == 1 && e[i].to == 2) DEBUG(cmn[v]);
                if(e[i].w > mn[e[i].to]) now = now-mn[e[i].to]+e[i].w,cmn[e[i].to] = mn[e[i].to],mn[e[i].to] = e[i].w;
                else if(e[i].w > cmn[e[i].to]) cmn[e[i].to] = e[i].w;
                mn[v] = cmn[v];
           //     if(v == 1 && e[i].to == 2) DEBUG(now);
            }
            else{
                if(e[i].w > mn[e[i].to]) now = now-mn[e[i].to]+e[i].w,cmn[e[i].to] = mn[e[i].to],mn[e[i].to] = e[i].w;
                else if(e[i].w > cmn[e[i].to]) cmn[e[i].to] = e[i].w;
            }
         //   if(v == 7 && e[i].to == 8) DEBUG(now);
            ans = std::max(ans,now);
            dfss(e[i].to,v);
            mn[v] = t1.fi;cmn[v] = t1.se;
            mn[e[i].to] = t2.fi;cmn[e[i].to] = t2.se;
            now = t;
        }
        //now = t;
    }

    inline void Solve(){
        dfs(1);ans = now; 
        dfss(1);
        printf("%lld\n",sm-ans);
    }
}

signed main(){
//    freopen("b.in","r",stdin);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,n-1){
        int u,v;scanf("%lld%lld",&u,&v);
        add(u,v);
    }
    Part1::Solve();
    Part2::Solve();
    return 0;
}


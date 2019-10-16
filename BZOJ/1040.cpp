/*
 * Author: RainAir
 * Time: 2019-08-30 21:17:34
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

int head[MAXN],du[MAXN],cnt,n,m;
LL val[MAXN];

inline void add(int u,int v){
    du[u]++;du[v]++;
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

bool circled[MAXN],vis[MAXN];
std::vector<int> circle;

inline void topsort(){
    std::queue<int> q;
    FOR(i,1,n) if(!du[i]) q.push(i);
    while(!q.empty()){
        int v = q.front();q.pop();
        circled[v] = false;vis[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(!--du[e[i].to]) q.push(e[i].to);
        }
    }
    FOR(i,1,n) m += circled[i];
}

inline void getcircle(int v){
    int t = v;circle.clear();int pre = -1;
    do{
        circle.pb(v);//vis[v] = true;
        bool flag = false,changed = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(e[i].to == t) flag = true;
            if(e[i].to == pre) continue;
            if(!vis[e[i].to]){
                changed = true;
                vis[e[i].to] = true;
                pre = v;v = e[i].to;
                break;
            }
        }
        if(flag && !changed) vis[t] = true,v = t;
    }while(v != t);
}

LL f[MAXN][2];
// 1:choose

inline void dp(int v,int fa=0){
    f[v][0] = 0;f[v][1] = val[v];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || circled[e[i].to]) continue;
        dp(e[i].to,v);
        f[v][0] += std::max(f[e[i].to][1],f[e[i].to][0]);
        f[v][1] += f[e[i].to][0];
    }
}

LL ff[MAXN][2];

inline LL dp2(){
    FOR(i,2,m){
        ff[i][0] = std::max(ff[i][0],ff[i][0]+std::max(ff[i-1][0],ff[i-1][1]));
        ff[i][1] = std::max(ff[i][1],ff[i-1][0]+ff[i][1]);
    }
    return std::max(ff[m][0],ff[m][1]);
}

signed main(){
    //int ttt = sizeof(ff)+sizeof(f)+sizeof(circled)+sizeof(vis)+sizeof(val)+sizeof(head)+sizeof(du)+sizeof(e)+3*sizeof(head);
    //DEBUG(ttt/1024/1024);
    scanf("%d",&n);
    std::fill(du+1,du+n+1,-1);
    std::fill(circled+1,circled+n+1,true);
    FOR(i,1,n){
        int x;scanf("%lld%d",val+i,&x);
        add(i,x);
    }
    topsort();LL ans = 0;
    FOR(i,1,n){
        if(!vis[i]){
            getcircle(i);m = circle.size();
            FOR(i,0,m-1){
                int x = circle[i];
                dp(x);ff[i+1][0] = f[x][0];
                ff[i+1][1] = f[x][1];
            }
            ff[1][1] = -1e18;LL res = dp2();
            FOR(i,0,m-1){
                int x = circle[i];
                ff[i+1][0] = f[x][0];
                ff[i+1][1] = f[x][1];
            }
            ff[1][0] = -1e18;ff[m][1] = -1e18;
            res = std::max(res,dp2());
            ans += res;
        }
    }
    printf("%lld\n",ans);
    return 0;
}

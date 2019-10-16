/*
 * Author: RainAir
 * Time: 2019-08-29 09:21:04
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
#define P std::pair<LL,LL>
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

int n,m;

struct Edge{
    int to,w,nxt;
}e[MAXN<<3];
int cnt = 1,head[MAXN<<1];

struct Opt{
    int u,v,w;
    Opt(int u=0,int v=0,int w=0) : u(u),v(v),w(w) {}
};
std::vector<Opt> buf;

inline void add(int u,int v,int w){
    buf.pb(Opt(u,v,w));
}
bool flag = false;

inline void addedge(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

inline void build(){
    cnt = 1;CLR(head,0);//DEBUG(n);
    FOR(i,0,(int)buf.size()-1){
        Opt x = buf[i];
        addedge(x.u,x.v,x.w);
//        if(flag)  printf("%lld %lld %lld\n",x.u,x.v,x.w);
    }
    buf.clear();
}

std::vector<int> q;

inline bool cmp(int x,int y){
    return e[x].w < e[y].w;
}

int dis[MAXN<<2],used[MAXN<<2],S,T;

inline void Dij(){
    std::priority_queue<P,std::vector<P>,std::greater<P> > q;
    FOR(i,0,T+23) dis[i] = 1e18,used[i] = false;
    q.push(MP(dis[S] = 0,S));
    while(!q.empty()){
        int v = q.top().se;q.pop();
        if(used[v]) continue;
        used[v] = true;
        for(int i = head[v];i;i = e[i].nxt){
            if(dis[e[i].to] > dis[v] + e[i].w){
                dis[e[i].to] = dis[v] + e[i].w;
                q.push(MP(dis[e[i].to],e[i].to));
            }
        }
    }
}

signed main(){
    freopen("2.in","r",stdin);
//    freopen("1.out","w",stdout);
    scanf("%lld%lld",&n,&m);
    FOR(i,1,m){
        int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);add(v,u,w);
    }
    build();
    S = 1,T = cnt+1;
    FOR(v,1,n){
        q.clear();
        for(int i = head[v];i;i = e[i].nxt){
            q.pb(i);
        }
        std::sort(all(q),cmp);
        FOR(i,0,(int)q.size()-1){
            int now = q[i];
            if(e[now].to == n) add(now,T,e[now].w);
            if(v == 1) add(S,now,e[now].w);
            add(now^1,now,e[now].w);
            if(i < (int)q.size()-1) add(q[i],q[i+1],e[q[i+1]].w-e[q[i]].w),add(q[i+1],q[i],0);
        }
    }flag = true;
    build();Dij();
    printf("%lld\n",dis[T]);
    return 0;
}

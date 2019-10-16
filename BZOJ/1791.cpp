/*
 * Author: RainAir
 * Time: 2019-08-29 17:41:22
 */
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <unordered_map>
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

inline char nc(){
    #define SIZE 2000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

inline void read(LL &x){
    x = 0;int flag = 0;char ch = nc();
    while(!isdigit(ch)){
        if(ch == '-') flag = 1;
        ch = nc();
    }
    while(isdigit(ch)){
        x = (x<<1) + (x<<3) + (ch^'0');
        ch = nc();
    }
    if(flag) x = -x;
}

struct Edge{
    int to,w,nxt,id;
}e[MAXN<<1];

std::unordered_map<LL,int> S;
int head[MAXN],cnt,n,deg[MAXN];

inline void add(int u,int v,int w,int id){
    if(u > v) std::swap(u,v);
    //if(S[u*n+v] >= w) return;
    S[1ll*u*n+v] = std::max(w,S[1ll*u*n+v]);
    deg[u]++;deg[v]++;
    e[++cnt] = (Edge){v,w,head[u],id};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v],id};head[v] = cnt;
}

std::vector<int> circle;
bool vis[MAXN];
bool circled[MAXN];
int fa[MAXN];

inline void topsort(){
    std::queue<int> q;
    FOR(i,1,n) if(deg[i] == 1) q.push(i);
    std::fill(circled+1,circled+n+1,true);
    while(!q.empty()){
        int v = q.front();q.pop();circled[v] = false;
        for(int i = head[v];i;i = e[i].nxt){
            if(--deg[e[i].to] == 1) q.push(e[i].to);
        }
    }
}

LL f[MAXN][2],len;

inline void dp(int v,int fa=-1){
    //LL mx = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa || circled[e[i].to]) continue;
        dp(e[i].to,v);
        if(f[e[i].to][0]+e[i].w > f[v][0]){
            f[v][1] = f[v][0];
            f[v][0] = f[e[i].to][0]+e[i].w;
        }
        else if(f[e[i].to][0]+e[i].w > f[v][1]) f[v][1] = f[e[i].to][0]+e[i].w;
  //      DEBUG(f[v][0]);
        //mx = std::max(mx,dp(e[i].to,v)+e[i].w);
    }
    len = std::max(len,f[v][0]+f[v][1]);
}

LL val[MAXN<<1],dis[MAXN<<1],tot;

inline LL calc(int u,int v){
    if(u > v) std::swap(u,v);
    return S[1ll*u*n+v];
}

struct Q{
    LL q[MAXN<<1];int ts[MAXN<<1];
    int head,tail;

    inline void clear(){
        FOR(i,0,tail) q[i] = ts[i] = 0;
        head = tail = 0;
    }

    inline void pop(int n,int t){
        // DEBUG(ts[tail]-ts[head]);
        while(head <= tail && t-ts[head] >= n) head++;
    }

    inline void push(LL x,int i){
        while(head <= tail && q[tail] <= x) tail--;
        q[++tail] = x;ts[tail] = i;
    }

    inline LL front(){
        return q[head];
    }

    inline void debug(){
        puts("---DEBUG BEGIN---");
        FOR(i,head,tail) printf("%lld %d\n",q[i],ts[i]);
        puts("---DEBUG END---");
    }
}q;

inline void dfs(int v,int fa=-1){
    circle.pb(v);vis[v] = true;//circled[v] = false;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
       // if(e[i].to == 5) DEBUG(vis[e[i].to]),DEBUG(circled[e[i].to]);
        if(vis[e[i].to]) continue;
        if(!circled[e[i].to]) continue;
        dfs(e[i].to,v);
    }
}

bool used[MAXN];

inline void Solve(){
    LL ans = 0;topsort();
    FOR(i,1,n){
        if(circled[i] && !used[i]){
            circle.clear();
            dfs(i);LL res = 0;
            FOR(i,0,(int)circle.size()-1){
                used[circle[i]] = true;len = 0;
                dp(circle[i]);
                val[i+1] = f[circle[i]][0];
//                DEBUG(val[i+1]);
                res = std::max(res,len);
                if(i > 0) dis[i+1] = calc(circle[i-1],circle[i]);
            }
            int sz = circle.size();
  //          DEBUG(sz);
          //  for(auto x:circle) DEBUG(x);
     /*       if(sz == 2){
                ans += calc(circle[0],circle[1])+val[1]+val[2];
                FOR(i,1,sz) val[i] = dis[i] = 0;
                continue;
            }*/
            dis[sz+1] = calc(circle[0],circle[(int)circle.size()-1]);
            val[sz+1] = val[1];
            FOR(i,2,sz) dis[i+sz] = dis[i],val[i+sz] = val[i];
            sz *= 2;
            //FOR(i,1,sz) printf("%lld %lld\n",dis[i],val[i]);
            FOR(i,1,sz) dis[i] += dis[i-1];
            //FOR(i,1,sz) printf("%lld %lld\n",dis[i],val[i]);
            // i < j: val[i]-dis[i]+val[j]+dis[j]
            q.clear();
            FOR(i,1,sz){
                q.pop(sz/2,i);
           //     DEBUG(q.front());DEBUG(val[i]);DEBUG(dis[i]);
                res = std::max(res,q.front()+val[i]+dis[i]);
           //     q.debug();
                q.push(val[i]-dis[i],i);
            }
            ans += res;
            FOR(i,1,sz) val[i] = dis[i] = 0;
            //DEBUG(res);
        }
    }
    printf("%lld\n",ans);
}

signed main(){
 //   freopen("30.in","r",stdin);
    read(n);//DEBUG(n);
    int mx = 0;
    FOR(u,1,n){
        int v,w;read(v);read(w);
        //scanf("%d%d",&v,&w);
        add(u,v,w,u);
        mx = std::max(mx,w);
    }
    Solve();
    return 0;
}


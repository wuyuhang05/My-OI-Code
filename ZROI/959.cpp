/*
 * Author: RainAir
 * Time: 2019-09-08 17:38:02
 */
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <assert.h>
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

inline char nc(){
    #define SIZE 200000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}

inline void read(int &x){
    x = 0;int flag = 0;
    char ch = nc();
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

const int MAXN = 2e5 + 5;
const int MAXV = 2e6 + 5;
const int MAXM = 19;

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];

int head[MAXN+233],cnt;
int f[MAXM+1][MAXN+233],g[MAXM+1][MAXN+233],dep[MAXN+233];
bool p[MAXV+233];
int prime[MAXV+233],d[MAXV+233],_cnt,n,q;

inline void prework(){
    d[1] = 1;
    FOR(i,2,MAXV-1){
        if(!p[i]) prime[++_cnt] = i,d[i] = i;
        for(int j = 1;j <= _cnt && i * prime[j] < MAXV;++j){
            p[i*prime[j]] = true;
            d[i*prime[j]] = prime[j];
            if(!(i%prime[j])) break;
        }
    }
}

inline void add(int u,int v,int w){
    e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

inline int gcd(int a,int b){
    return !b ? a :gcd(b,a%b);
}

inline void dfs(int v,int fa=0){
    FOR(i,1,MAXM){
        f[i][v] = f[i-1][f[i-1][v]];
        g[i][v] = gcd(g[i-1][v],g[i-1][f[i-1][v]]);
    }
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        f[0][e[i].to] = v;g[0][e[i].to] = e[i].w;
        dep[e[i].to] = dep[v] + 1;
        dfs(e[i].to,v);
    }
}

inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,MAXM) if((1<<i)&d) x = f[i][x];
    }
    if(x == y) return x;
    ROF(i,MAXM,0){
        if(f[i][x] == f[i][y]) continue;
        x = f[i][x],y = f[i][y];
    }
    return f[0][x];
}

inline int cal(int x,int y){ // x to lca
    if(dep[x] < dep[y]) std::swap(x,y);
    int d = dep[x] - dep[y],ans = 0;
    FOR(i,0,MAXM){
        if((1<<i)&d) ans = gcd(g[i][x],ans),x = f[i][x];
    }
    return ans;
}

inline int calc(int x,int y){ // normal
    int l = lca(x,y);
    return gcd(cal(l,x),cal(l,y));
}

std::unordered_map<U LL,LL> S;
//std::unordered_map<LL,P> chk;

inline int dp(int v,int fa,int d){
    int ans = 0;
    U LL tags = 1ull*fa*19260817*19260817+1ll*v*19260817+d;
    if(S.count(tags)) return S[tags];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        if(e[i].w % d) continue;
        ans = std::max(ans,dp(e[i].to,v,d)+1);
    }
    return S[tags] = ans;
}

inline int kthfa(int v,int k){
    FOR(i,0,MAXM){
        if((1<<i)&k) v = f[i][v];
    }
    return v;
}

inline int dis(int x,int y){
    return dep[x]+dep[y]-2*dep[lca(x,y)];
}

int main(){
//    freopen("ex_tree2.in","r",stdin);
  //  freopen("sdasd.in","r",stdin);
 //   freopen("a.in","r",stdin);
 //   freopen("sdssd.out","w",stdout);
    prework();
    read(n);read(q);
    FOR(i,1,n-1){
        int u,v,w;
        read(u);read(v);read(w);
        add(u,v,w);
    }
    dfs(1,0);
    FOR(i,1,q){
        int x,y;read(x);read(y);
        if(x == y){
            puts("1");
            continue;
        }
        int l = lca(x,y),g = calc(x,y);
        if(g == 1){
            printf("%d\n",dis(x,y));
            continue;
        }
        int fx = f[0][x],fy = f[0][y];
        if(l == x) fx = kthfa(y,dep[y]-dep[x]-1);
        else if(l == y) fy = kthfa(x,dep[x]-dep[y]-1);
        // 限制不走相同的子树 qaq
        int mxdis = dp(x,fx,1) + dp(y,fy,1);
    //    DEBUG(mxdis);
        int ans = 0;
        while(g != 1){
            int p = d[g];//assert(d[g]);
            ans = std::max(ans,dp(x,fx,p)+dp(y,fy,p));
            if(ans == mxdis) break;
            while(!(g%p)) g /= p;
        }
        printf("%d\n",ans == mxdis ? -1 : ans+dis(x,y)+1);
    }
    return 0;
}



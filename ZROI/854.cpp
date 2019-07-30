/*
 * Author: RainAir
 * Time: 2019-07-26 08:37:57
 * 为什么这么慢呢...2
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

inline char nc(){
    #define SIZE 200000+1
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
//#define read(x) scanf("%d",&x)

const int MAXN = 2e6 + 5;
//P q[MAXN];
struct Edge{
    int to,nxt;
}e[MAXN<<1];
int cnt;int head[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int lgyak[MAXN],dep[MAXN];
int n,m,X,Y;
inline void dfs(int v,int fa=0){
    for(int i = head[v];i;i = e[i].nxt){
        int x = e[i].to;
        if(x == fa) continue;
        lgyak[x] = v;
        dep[x] = dep[v] + 1;
        dfs(x,v);
    }
}
/*
inline int lca(int x,int y){
    if(dep[x] != dep[y]){
        if(dep[x] < dep[y]) std::swap(x,y);
        int d = dep[x]-dep[y];
        FOR(i,0,LOG){
            if((1<<i)&d) x = f[i][x];
        }
    }
    if(x == y) return x;
    ROF(i,LOG,0){
        if(f[i][x] == f[i][y]) continue;
        x = f[i][x],y = f[i][y];
    }
    return f[0][x];
}
*/
int ans[MAXN];

int F[MAXN];
inline int find(int x){
    return x == F[x] ? x : F[x] = find(F[x]);
}

int main(){
   //freopen("test.in","r",stdin);
  //  freopen("a.out","w",stdout);
    read(n);read(m);
    FOR(i,2,n){
        int x;read(x);
        add(i,x);
      //  G[x].pb(i);G[i].pb(x);
    }
    read(X);read(Y);
    dep[1] = 1;dfs(1);
    FOR(i,1,n) F[i] = i;
    int u=X,v=Y;
    FOR(i,1,m){
        int x = find(u),y = find(v);
        while(x != y && (x != 1 || y != 1)){
            if(dep[x] < dep[y]) std::swap(x,y);
            ans[x] = i;F[x] = find(lgyak[x]);
            x = F[x];
        }
        int tu = u,tv = v;
        u = (1ll*tu*114514%n+1ll*tv*1919810%n)%n+1;
        v = (1ll*tu*415411%n+1ll*tv*8101919%n)%n+1;
    }
    LL sm = 0;
    FOR(i,1,n) sm += ans[i];
    printf("%lld\n",sm);
    return 0;
}

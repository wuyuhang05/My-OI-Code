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
const int ha = 998244353;

inline char nc(){
    #define SIZE 1000000+3
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

int n,p;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int inv[MAXN];

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int f[MAXN],g[MAXN],h[MAXN],sz[MAXN],pre[MAXN],suf[MAXN],ans;
std::vector<int> son;

inline int calc(int x){
    return (1ll*(p+ha-1)%ha*inv[x]%ha+1)%ha;
}

inline void dfs(int v,int fa=0){
    sz[v] = 1;h[v] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        sz[v] += sz[e[i].to];
        h[v] = 1ll*h[v]*f[e[i].to]%ha;
    }
    f[v] = 1ll*h[v]*calc(sz[v])%ha;
}

inline void dfs2(int v,int fa=0){
    ans = (ans+1ll*h[v]*g[v]%ha*calc(n)%ha)%ha;
    son.clear();son.pb(0);
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        son.pb(e[i].to);
    }
    pre[0] = 1;
    FOR(i,1,(int)son.size()-1) pre[i] = 1ll*pre[i-1]*f[son[i]]%ha;
    suf[(int)son.size()] = 1;
    ROF(i,(int)son.size()-1,1) suf[i] = 1ll*suf[i+1]*f[son[i]]%ha;
    FOR(i,1,(int)son.size()-1)
        g[son[i]] = 1ll*pre[i-1]*suf[i+1]%ha*g[v]%ha*calc(n-sz[son[i]])%ha;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs2(e[i].to,v);
    }
}

signed main(){
    freopen("treap.in","r",stdin);
    freopen("treap.out","w",stdout);
    read(n);read(p);
    inv[1] = 1;FOR(i,2,n) inv[i] = 1ll*(ha-ha/i)*inv[ha%i]%ha;
    FOR(i,1,n-1){
        int u,v;read(u);read(v);
        add(u,v);add(v,u);
    }
    dfs(1);g[1] = 1;
    dfs2(1);
    ans = 1ll*ans*qpow(n)%ha;
    printf("%d\n",ans);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-27 17:04:20
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

const int MAXN = 2000+5;
const int ha = 998244353;

struct Edge{
    int to,nxt,l,r;
}e[MAXN<<1];
int head[MAXN],cnt,n,m;

inline void add(int u,int v,int l,int r){
    e[++cnt] = (Edge){v,head[u],l,r};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v],l,r};head[v] = cnt;
}

struct Node{
    int x,w;
    bool operator < (const Node &t) const {
        return w < t.w;
    }
}a[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int f[MAXN][MAXN],tmp[MAXN]; // v 子树是被 i 江尸干死的
std::bitset<MAXN> son[MAXN]; // v 子树的江尸集

inline void dfs(int v,int fa=0){
    int ps = 1;
    FOR(i,1,m){
        if(a[i].x == v){
            ps = i;
            son[v][i] = 1;
        }
    }
    FOR(i,ps,m) f[v][i] = 1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        FOR(j,1,m) tmp[j] = f[v][j],f[v][j] = 0;
        int pre = 0;
        FOR(j,1,m){
            int x = std::max(0,std::min(e[i].r-e[i].l+1,e[i].r-a[j].w+1));
            if(son[e[i].to][j]) (pre += f[e[i].to][j]) %= ha;
            else (f[v][j] += 1ll*tmp[j]*pre%ha*x%ha) %= ha;
        }
        int suf = 0;
        ROF(j,m,1){
            int x = std::max(0,std::min(e[i].r-e[i].l+1,e[i].r-a[j].w+1));
//            if(son[e[i].to][j]) 
                (suf += 1ll*f[e[i].to][j]*x%ha) %= ha;
//            else 
                (f[v][j] += 1ll*tmp[j]*suf%ha) %= ha;
        }
        FOR(j,1,m){
            int x = std::max(0,std::min(e[i].r-e[i].l+1,a[j].w-e[i].l));
            (f[v][j] += 1ll*tmp[j]*f[e[i].to][j]%ha*x%ha) %= ha;
        }
        son[v] |= son[e[i].to];
    }
}

inline void clear(){
    FOR(i,1,n) son[i].reset(),head[i] = 0,tmp[i] = 0;
    FOR(i,1,n) FOR(j,1,m) f[i][j] = 0;
    cnt = 0;
}

inline void Solve(){
    scanf("%d%d",&n,&m);
    int ans = 0,tot = 1;
    FOR(i,1,n-1){
        int u,v,l,r;scanf("%d%d%d%d",&u,&v,&l,&r);
        add(u,v,l,r);tot = 1ll*tot*(r-l+1)%ha;
    }
    FOR(i,1,m) scanf("%d%d",&a[i].x,&a[i].w);
    std::sort(a+1,a+m+1);
    dfs(1);
    FOR(i,1,m) (ans += f[1][i]) %= ha;
    ans = (tot+ha-ans)%ha;
    printf("%lld\n",1ll*ans*qpow(tot)%ha);
    clear();
}

int main(){
   // freopen("a.in","r",stdin);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-24 17:17:43
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
#define int LL
const int MAXN = 2000+5;
const int ha = 998244353;

struct Edge{
    int to,nxt;
}e[MAXN<<3];
int head[MAXN],cnt;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

struct Node{
    int A,B,C;
}F[MAXN];
int ans[MAXN],n,du[MAXN],f[MAXN];
std::vector<int> son[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(a < 0) a += ha;
    a = (a+ha)%ha;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void dfs(int v,int fa=0,int faa=0){
    int sonA = 0,sonB = 0,sonC = 0;
    int ssonA = 0,ssonC = 0;
    int ssonBA = 0,ssonBB = 0,ssonBC = 0;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v,fa);
        (sonA += F[e[i].to].A) %= ha;
        (sonB += F[e[i].to].B) %= ha;
        (sonC += F[e[i].to].C) %= ha;
    }
    for(auto x:son[v]){
        (ssonA += F[x].A) %= ha;
        (ssonC += F[x].C) %= ha;
        (ssonBB += 1ll*F[x].B*F[f[x]].B%ha) %= ha;
        (ssonBA += 1ll*F[x].B*F[f[x]].A%ha) %= ha;
        (ssonBC += 1ll*F[x].B*F[f[x]].C%ha) %= ha;
    }
    int A = qpow(du[v]-sonB-ssonA-ssonBB);
    int B = 1ll*(sonA+ssonBA+1)%ha*A%ha;
    int C = 1ll*(ssonC+sonC+ssonBC+du[v])%ha*A%ha;
    F[v] = (Node){A,B,C};
}

inline void ddfs(int v,int fa=0,int faa=0){
    ans[v] = (1ll*F[v].A*ans[faa]%ha+1ll*F[v].B*ans[fa]%ha+F[v].C)%ha;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        ddfs(e[i].to,v,fa);
    }
}

signed main(){
    freopen("b.in","r",stdin);
    freopen("b.out","w",stdout);
    scanf("%lld",&n);
    FOR(i,2,n){
        scanf("%lld",f+i);
        add(f[i],i);//add(i,f);
        du[f[i]]++;du[i]++;
    }
    FOR(i,2,n) if(f[f[i]]) du[f[f[i]]]++,du[i]++,son[f[f[i]]].pb(i);
    dfs(1);
    FOR(i,2,n) DEBUG(F[1].A)
    ;F[1].A = F[1].B = F[1].C = 0;
    ddfs(1);
    FOR(i,1,n) printf("%lld\n",ans[i]);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-11-07 19:54:01
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

const int MAXN = 2e5 + 5;
const int ha = 10007;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int inv2;

inline void add(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int val[MAXN];
int ans1 = 0,ans2 = 0;

inline void dfs(int v,int fa=0){
    int sm1 = 0,sm2 = 0,mx = 0,se = -1;
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        (sm1 += val[e[i].to]) %= ha;
        (sm2 += 1ll*val[e[i].to]*val[e[i].to]%ha) %= ha;
        if(val[e[i].to] > mx){
            se = mx;mx = val[e[i].to];
        }
        else if(val[e[i].to] > se){
            se = val[e[i].to];
        }
    }
//    DEBUG(sm1);DEBUG(sm2);
    ans1 = std::max(ans1,std::max(mx*se,mx*val[fa]));
    (ans2 += 2ll*val[fa]%ha*sm1%ha) %= ha;
    int gx = (1ll*sm1*sm1%ha+ha-sm2)%ha;
    (ans2 += gx) %= ha;
}

int n;

int main(){
    scanf("%d",&n);inv2 = qpow(2);
    FOR(i,2,n){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);
    }
    FOR(i,1,n) scanf("%d",val+i);
    dfs(1);
    printf("%d %d\n",ans1,ans2);
    return 0;
}

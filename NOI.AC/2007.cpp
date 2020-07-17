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
#define db double
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

const int MAXN = 1e5 + 5;

int n,m,q;
int a[MAXN];

struct Edge{
    int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int du[MAXN],BLO;
std::map<P,int> S;

inline void add(int u,int v){
    if(u == v) return;
    if(u > v) std::swap(u,v);
    ++du[u];++du[v];
    if(S[MP(u,v)]){
        int t = S[MP(u,v)];
        e[t].w++;e[t+1].w++;
        return;
    }
    S[MP(u,v)] = cnt+1;
    e[++cnt] = (Edge){v,1,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,1,head[v]};head[v] = cnt;
}

std::vector<P> nei[MAXN];
int sm[MAXN],b[MAXN];

int main(){
//    freopen("A.in","r",stdin);
 //   freopen("A.out","w",stdout);
    scanf("%d%d%d",&n,&m,&q);
    FOR(i,1,n) scanf("%d",a+i);
    add(m+1,a[1]);
    FOR(i,2,n) add(a[i-1],a[i]);
    add(a[n],m+2);m += 2;BLO = std::sqrt(1.0*m);
    FOR(v,1,m){
        if(du[v] > BLO){
            for(int i = head[v];i;i = e[i].nxt){
                nei[e[i].to].pb(MP(v,e[i].w));
            }
        }
    }
    int ans = 0;
    FOR(ccc,1,q){
        int v;scanf("%d",&v);
        b[v] ^= 1;
       // int res = 0;
        if(du[v] <= BLO){
            for(int i = head[v];i;i = e[i].nxt){
                if(b[v] == b[e[i].to]) ans -= e[i].w;
                else ans += e[i].w;
            }
        }
        else{
            if(b[v]) ans -= sm[v],ans += du[v]-sm[v];
            else ans -= du[v]-sm[v],ans += sm[v];
        }
        FOR(i,0,(int)nei[v].size()-1){
            int x = nei[v][i].fi,w = nei[v][i].se;
            if(b[v] == 1) sm[x] += w;
            else sm[x] -= w;
        }
     //   DEBUG(ans);
        printf("%d\n",ans/2);
    }
    return 0;
}
/*
有若干(ai,bi) 询问 c[a[i]]=1 & c[b[i]]=0 的二元组个数
前后补 0 变成 c[a[i]] != c[b[i]] 个数 /2
取反变成 c[a[i]]=c[b[i]] 个数
<sqrt(n): 暴力更新
>sqrt(n): 预先维护处相连的所有点的 1 的个数和
TC: O(nsqrt(n))
*/

/*
 * Author: RainAir
 * Time: 2019-07-25 07:53:55
 */
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
#define int LL
struct Edge{
    int u,v,w;
    bool operator < (const Edge &t) const {
        return w < t.w;
    }
}e[MAXN];
int n,m,k;
std::unordered_map<int,int> S;
int f[1000][1000];
int cnt;
std::vector<int> ans;

signed main(){
    scanf("%lld%lld%lld",&n,&m,&k);
    FOR(i,1,m) scanf("%lld%lld%lld",&e[i].u,&e[i].v,&e[i].w);
    std::sort(e+1,e+m+1);
    FOR(i,1,999) FOR(j,1,999) f[i][j] = 1e18;
    FOR(i,1,999) f[i][i] = 0;
    FOR(i,1,std::min(k,m)){
        if(!S[e[i].u]) S[e[i].u] = ++cnt;
        if(!S[e[i].v]) S[e[i].v] = ++cnt;
        int u = S[e[i].u],v = S[e[i].v];
        f[u][v] = f[v][u] = e[i].w;
    }
    FOR(k,1,cnt){
        FOR(i,1,cnt){
            FOR(j,1,cnt){
                f[i][j] = std::min(f[i][k]+f[k][j],f[i][j]);
            }
        }
    }//DEBUG(cnt);
    /*
    FOR(i,1,cnt){
        FOR(j,1,cnt) printf("%lld ",f[i][j]);
        puts("");
    }*/
    FOR(i,1,cnt) FOR(j,1,i-1) if(f[i][j] != 0 && f[i][j] != 1e9) ans.pb(f[i][j]);
    std::sort(all(ans));
    printf("%lld\n",ans[k-1]);
    return 0;
}

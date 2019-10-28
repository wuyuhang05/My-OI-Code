/*
 * Author: RainAir
 * Time: 2019-10-28 08:25:54
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
const int MAXN = 1e6 + 5;
int sm1[MAXN],sm2[MAXN];
int f[MAXN],g[MAXN];
int s[MAXN],n,d;

inline void Solve(int f[]){
    FOR(i,1,n) sm1[i] = sm2[i] = 0;
    FOR(i,1,n){
        sm1[i] = sm1[i-1]+(i*2-1)*s[i];
        sm2[i] = sm2[i-1]+s[i];
    }
    f[1] = s[1]*d*d;
    FOR(i,2,n){
        f[i] = f[i-1];
        int gx = 2*d-1;
        gx -= 2*(i-1)-1;
        f[i] -= (sm1[i-1]-sm1[std::max(i-d-1,0ll)])+gx*(sm2[i-1]-sm2[std::max(i-d-1,0ll)]);
        f[i] += d*d*s[i];
    }
}

signed main(){
    freopen("weather.in","r",stdin);
    freopen("weather.out","w",stdout);
    scanf("%lld%lld",&n,&d);
    FOR(i,1,n) scanf("%lld",s+i);
    Solve(f);
//    FOR(i,1,n) DEBUG(f[i]);
    std::reverse(s+1,s+n+1);
    Solve(g);
    std::reverse(g+1,g+n+1);
    int ans = 0;
    FOR(i,0,n) ans = std::max(ans,f[i]+g[i+1]);
    printf("%lld\n",ans);
    return 0;
}


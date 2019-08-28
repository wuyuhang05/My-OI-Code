/*
 * Author: RainAir
 * Time: 2019-08-26 15:25:51
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 20+5;

int D[MAXN],fac[MAXN];

inline void prework(){
    D[1] = 0;D[2] = 1;
    FOR(i,3,MAXN-1) D[i] = (i-1)*(D[i-1]+D[i-2]);
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = fac[i-1]*i;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return fac[n]/fac[m]/fac[n-m];
}

inline void Solve(){
    int n,m;scanf("%lld%lld",&n,&m);
    int ans = C(n,m)*D[m];
    printf("%lld\n",ans);
}

signed main(){
    prework();
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

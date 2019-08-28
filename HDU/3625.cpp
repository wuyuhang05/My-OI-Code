/*
 * Author: RainAir
 * Time: 2019-08-26 16:56:54
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
const int MAXN = 20 + 5;

int S[MAXN][MAXN];

inline void prework(){
    S[0][0] = 1;
    FOR(i,1,MAXN-1){
        FOR(j,1,i){
            S[i][j] = (i-1)*S[i-1][j]+S[i-1][j-1];
        }
    }
}

inline void Solve(){
    int n,k;scanf("%lld%lld",&n,&k);
    int s1 = 0,s2 = 0;
    FOR(i,1,n){
        if(i <= k) s1 += S[n][i]-S[n-1][i-1];
        s2 += S[n][i];
    }
    printf("%.4f\n",1.0*s1/s2);
}

signed main(){
    prework();
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

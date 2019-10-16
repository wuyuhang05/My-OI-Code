/*
 * Author: RainAir
 * Time: 2019-10-07 20:12:05
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
const int MAXN = 60+5;
const int ha = 10000007;
int f[MAXN][MAXN][2];
// 前 i 位，有 j 个 1，卡上界，前导 0
int a[MAXN],len;
int c[MAXN][MAXN];

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int dfs(int i,int j,int lim){
    if(f[i][j][lim] != -1) return f[i][j][lim];
    if(i < j) return 0;
    if(!j) return 1;
    int ans = 0;
    if(lim){
        if(a[i]) ans += dfs(i-1,j,0)+dfs(i-1,j-1,1);
        else ans += dfs(i-1,j,1);
    }
    else{
        ans += dfs(i-1,j,0);
        ans += dfs(i-1,j-1,0);
    }
    return f[i][j][lim] = ans;
}

signed main(){
    int n;scanf("%lld",&n);
    while(n) a[++len] = n&1,n >>= 1;
    CLR(f,-1);int ans = 1;
//    DEBUG(dfs(1,2,1,1));exit(0);
    FOR(i,1,MAXN-1){
        (ans *= qpow(i,dfs(len,i,1)))%=ha;
    }
    printf("%lld\n",ans);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-11-01 14:54:40
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

const int MAXN = 200+5;
int n,ha;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int getf(int,int);
int getg(int,int);

int f[MAXN][MAXN],g[MAXN][MAXN],dp[MAXN][MAXN];

inline int getf(int i,int j){
    if(f[i][j] != -1) return f[i][j];
    return f[i][j] = getg(i-1,j-1);
}

inline int getg(int i,int j){
    if(j < 0) return 0;
    if(!i) return 1;
    if(!j) return 0;
    if(g[i][j] != -1) return g[i][j];
    int &res = g[i][j];res = 0;
    FOR(k,1,i){
        (res += 1ll*getg(i-k,j)*getf(k,j)%ha*dp[i][k]%ha) %= ha;
    }
    return res;
}

int t[MAXN];

int main(){
//    freopen("toy.in","r",stdin);
//    freopen("toy.out","w",stdout);
    scanf("%d%d",&n,&ha);
    CLR(f,-1);CLR(g,-1);
    dp[1][1] = 1;
    FOR(i,2,n){
        FOR(j,1,i){
            int inv = qpow(i);
            dp[i][j] = (1ll*dp[i-1][j-1]*(j-1)%ha*inv%ha+1ll*dp[i-1][j]*(i-j)%ha*inv%ha)%ha;
        }
    }
    FOR(i,1,n) t[i] = getf(n,i);
    ROF(i,n,1) t[i] = (t[i]+ha-t[i-1])%ha;
    int ans = 0;
    FOR(i,2,n) (ans += 1ll*t[i]*(i-1)%ha) %= ha;
    printf("%lld\n",1ll*ans%ha);
    return 0;
}

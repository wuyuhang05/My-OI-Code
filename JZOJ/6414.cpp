/*
 * Author: RainAir
 * Time: 2019-11-07 16:01:06
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

const int MAXN = 500+5;
const int ha = 998244353;

int fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n&1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int n,k;
bool del[MAXN];
int f[MAXN][MAXN],g[MAXN][MAXN],dp[MAXN][MAXN];

inline int getf(int,int);
inline int getg(int,int);

inline int getf(int i,int j){
    if(del[i]) return f[i][j] = 0;
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
        (res += 1ll*getf(k,j)*getg(i-k,j)%ha*C(i-1,k-1)%ha) %= ha;
    }
    return res;
}

int ans[MAXN];

int main(){
    freopen("subtree.in","r",stdin);
    freopen("subtree.out","w",stdout);
    prework();
    scanf("%d%d",&n,&k);
    FOR(i,1,k){
        int x;scanf("%d",&x);
        del[x] = true;
    }
    CLR(f,-1);CLR(g,-1);
   // DEBUG(getg(2,2));
   // return 0;
    FOR(i,1,n) ans[i] = getf(n,i);
    ROF(i,n,1) ans[i] = (ans[i]+ha-ans[i-1]) % ha;
    int l,r;scanf("%d%d",&l,&r);
    FOR(i,l,r) printf("%d ",ans[i]);
    puts("");
    return 0;
}

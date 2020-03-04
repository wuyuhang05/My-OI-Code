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

const int MAXN = 1e6 + 5;
const int ha = 998244353;
bool x[MAXN],y[MAXN];
int fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
int n,m;

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int binom(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    scanf("%d",&n);
    prework();
    FOR(i,1,n){
        int p;scanf("%d",&p);
        if(p == i){
            puts("0");return 0;
        }
        if(p) x[p] = y[i] = true,++m;
    }
    // DEBUG(1);
    int cnt = 0,ans = 0;
    FOR(i,1,n) cnt += !(x[i]|y[i]);
    FOR(i,0,cnt){
        int gx = 1ll*binom(cnt,i)*fac[n-m-i]%ha;
        // DEBUG(gx);
        if(i&1) gx = ha-gx;
        (ans += gx) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}
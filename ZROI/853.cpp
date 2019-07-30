/*
 * Author: RainAir
 * Time: 2019-07-21 09:07:23
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
const int MAXN = 5000+5;
const int ha = 1e9 + 7;
LL fac[MAXN],inv[MAXN];

inline LL qpow(LL a,LL n=ha-2){
    LL res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
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

int n,q;

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}
int m;
inline int calc(int s){
    int ans = fac[n-m];
    FOR(i,1,s)
        ans = (ans + ((i&1) ? -1 : 1)*C(s,i)*fac[n-m-i]%ha+ha)%ha;
    return ans;
}
bool vis1[MAXN],vis2[MAXN];

signed main(){
    //freopen("test.in","r",stdin);
    //freopen("test1.out","w",stdout);
    prework();
    scanf("%lld%lld",&n,&q);
    printf("%lld\n",calc(n));
    int t = n;
    FOR(i,1,q){
        ++m;int pos,x;scanf("%lld%lld",&pos,&x);
        vis1[pos] = vis2[x] = true;int cnt = 0;
        FOR(j,1,n) if(!vis1[j] && !vis2[j]) ++cnt;
        printf("%lld\n",calc(cnt));
    }
    return 0;
}



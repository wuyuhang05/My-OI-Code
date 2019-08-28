/*
 * Author: RainAir
 * Time: 2019-08-18 18:11:20
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
const int MAXN = 1000000+5;
const int ha = 1000000007;
int prime[MAXN],phi[MAXN],g[MAXN],inv[MAXN],cnt;
bool p[MAXN];

inline void prework(int n){
    phi[1] = 1;
    FOR(i,2,n){
        if(!p[i]) prime[++cnt] = i,phi[i] = i-1;
        for(int j = 1;j <= cnt && i*prime[j] <= n;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])){
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }
            phi[i*prime[j]] = phi[i]*phi[prime[j]];
        }
    }
    FOR(i,1,n) (phi[i] += phi[i-1]) %= ha;
    inv[1] = 1;
    FOR(i,2,n) inv[i] = (ha-ha/i)*inv[ha%i]%ha;
}

inline int calc1(int x){
    return (phi[x]*2ll%ha+ha-1)%ha;
}

inline int qpow(int a,int n=ha-2){
    int res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int x,n;

inline int calc(int n){
    if(x == 1) return n;
    return ((qpow(x,n+1)-x+ha)%ha*inv[x-1]%ha)%ha;
}

inline int calc2(int l,int r){
    int a = calc(l-1),b = calc(r);
    int res = (b-a+ha)%ha;
    res = (res-(r-l+1)+ha)%ha;
    return res;
}

inline void Solve(){
    scanf("%lld%lld",&x,&n);int ans = 0;
    for(int l = 1,r;l <= n;l = r+1){
        r = n/(n/l);
        (ans += calc2(l,r)*calc1(n/l)%ha)%=ha;
    }
    printf("%lld\n",ans);
}

signed main(){
    prework(1000000);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

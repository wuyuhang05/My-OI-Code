/*
 * Author: RainAir
 * Time: 2019-08-26 19:37:47
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
inline int qpow(int a,int n,int ha){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;return;
    }
    exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
}

inline int inv(int a,int p){
    int x,y;exgcd(a,p,x,y);
    return (x+p)%p;
}

int f[9765625+233];

inline void init(int p,int pe){
    f[0] = 1;
    FOR(i,1,pe){
        f[i] = f[i-1];
        if(i%p) f[i] = f[i]*i%pe;
    }
}

inline int fac(int n,int p,int pe){
    int ans = 1;
    if(!n) return 1;
    /*FOR(i,1,pe){
        if(i%p) ans = 1ll*ans*i%pe;
    }*/
    ans = f[pe];
    ans = qpow(ans,n/pe,pe);
    /*FOR(i,1,n%pe){
        if(i%p) ans = 1ll*ans*i%pe;
    }*/
    ans = 1ll*ans*f[n%pe]%pe;
    return ans*fac(n/p,p,pe)%pe;
}

inline int C(int n,int m,int mod,int p,int pe){
    init(p,pe);
    if(n < m) return 0;
    int a = fac(n,p,pe),b = fac(m,p,pe),c = fac(n-m,p,pe);
    int k = 0;
    for(int i = n;i;i /= p) k += i/p;
    for(int i = m;i;i /= p) k -= i/p;
    for(int i = n-m;i;i /= p) k -= i/p;
    int ans = 1ll*a*inv(b,pe)%pe*inv(c,pe)%pe*qpow(p,k,pe)%pe;
    ans = ans*(mod/pe)%mod*inv(mod/pe,pe)%mod;
    return ans;
}

signed main(){
    int n,m,mod;scanf("%lld%lld",&n,&m);mod = 1e10;
    int ans = C(n,m,mod,2,1024);
    ans = (ans+C(n,m,mod,5,9765625))%mod;
    bool flag = false;long double t=1;
    if(n-m < m) m = n-m;
    FOR(i,1,m){
        t = t*(n-i+1)/i;
        if(t >= 10000000000.0){
            flag = true;
            break;
        }
    }
    if(flag) printf("...%010lld\n",ans);
    else printf("%lld\n",ans);
    return 0;
}

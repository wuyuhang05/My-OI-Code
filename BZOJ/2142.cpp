/*
 * Author: RainAir
 * Time: 2019-07-21 19:54:36
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
const int MAXN = 1000+5;
int a[MAXN],n,m,mod;

inline int qpow(int a,int n,int ha){
    int res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return;
    }
    exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
}

inline int inv(int a,int p){
 //   assert(p != 0);
    int x = 0,y = 0;
    exgcd(a,p,x,y);
    x = (x%p+p)%p;
   // assert(x != 0);
    return x;
}

inline int fac(int n,int p,int pk){
    int ans = 1ll;
    if(!n) return 1;
    FOR(i,1,pk){
        if(i%p) ans = 1ll*ans*i%pk;
    }
    ans = qpow(ans,n/pk,pk);
    FOR(i,1,n%pk){
        if(i % p) ans = 1ll*ans*i%pk;
    }
    return 1ll*ans*fac(n/p,p,pk)%pk;
}

inline int C(int n,int m,int mod,int p,int pk){
    if(n < m) return 0;
    int ans = 1ll;
    int a = fac(n,p,pk),b = fac(m,p,pk),c = fac(n-m,p,pk);
    int k = 0;
    for(int i = n;i;i /= p) k += i/p;
    for(int i = m;i;i /= p) k -= i/p;
    for(int i = n-m;i;i /= p) k -= i/p;
    ans = 1ll*a*inv(b,pk)%pk*inv(c,pk)%pk*qpow(p,k,pk)%pk;
    return 1ll*ans*(mod/pk)%mod*inv(mod/pk,pk)%mod;
}

LL ans = 1ll;

signed main(){
    scanf("%lld%lld%lld",&mod,&n,&m);int sm = 0;
    FOR(i,1,m) scanf("%lld",a+i),sm += a[i];
    if(sm > n){
        puts("Impossible");
        return 0;
    }
    int q = std::sqrt(1.0*mod);
    FOR(i,1,m){
        int x = mod,res = 0;
        FOR(k,2,q){
            if(!(x%k)){
                int pk = 1;
                while(!(x%k)) x /= k,pk *= k;
                res = (res+C(n,a[i],mod,k,pk))%mod;
            }
        }
        if(x > 1) res = (res+C(n,a[i],mod,x,x))%mod;
        ans = 1ll*ans*res%mod;
        n -= a[i];
    }
    printf("%lld\n",ans);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-08-20 20:13:59
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
const int ha = 1e9 + 7;

inline int phi(int x){
    int q = std::sqrt(1.0*x),ans = 1ll;
    FOR(i,2,q){
        if(!(x%i)){
            x /= i;ans *= (i-1);
            while(!(x%i)) x /= i,ans *= i;
        }
    }
    if(x != 1) ans *= (x-1);return ans;
}

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int calc(int n){
    int ans = 0,q = std::sqrt(1.0*n);
    FOR(i,1,q){
        if(n%i) continue;
        (ans += qpow(n,i-1)*phi(n/i)%ha) %= ha;
        if(i*i != n) (ans += qpow(n,n/i-1)*phi(i)%ha) %= ha;
    }
    return ans;
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--){
        int x;scanf("%lld",&x);
        printf("%lld\n",calc(x));
    }
    return 0;
}

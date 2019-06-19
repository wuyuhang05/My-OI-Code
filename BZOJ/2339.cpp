#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 1e6 + 5;
const int ha = 100000007;

LL f[MAXN],a[MAXN],n,m,ans;

inline LL qpow(LL a,LL n){
    LL res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void pre(){
    a[0] = 1;
    FOR(i,1,m) a[i] = (a[i-1]*((ans-i+1+ha)%ha))%ha;
    FOR(i,3,m) f[i] = (a[i-1]-f[i-1]-(f[i-2]*(i-1)%ha*(ans-(i-2))%ha)+ha)%ha;
}

int main(){
    scanf("%lld%lld",&n,&m);
    ans = qpow(2,n);
    if(--ans<0) ans += ha;
    pre();
    ans = 1;
    FOR(i,2,m) ans = (ans*i)%ha;
    f[m] = (f[m]*qpow(ans,ha-2)%ha+ha)%ha;
    printf("%lld\n",f[m]%ha);
    return 0;
}

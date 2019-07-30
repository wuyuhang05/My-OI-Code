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
#define FOR(i,a,b) for(Re LL i = a;i <= b;++i)
#define ROF(i,a,b) for(Re LL i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int prime[] = {0,2,3,5,7,11,13,17,19,23};

inline int qpow(int a,int n,int ha){
    int res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline bool chk(int x,int p){
    if(x == p) return true;
    if(!(x%p)) return false;
    if(qpow(x,p-1,p) != 1) return false;
    int k = x-1;
    while(!(k&1)){
        k >>= 1;
        int t = qpow(p,k,x);
        if(t != 1 && t != x-1) return false;
        if(t == x-1) return true;
    }
    return true;
}

inline bool isprime(int x){
    if(x < 2) return false;
    FOR(i,1,9) if(!chk(x,prime[i])) return false;
    return true;
}

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline LL calc(int x,int t){
    LL v0 = 1+1ll*rand()*rand()%x,v = (v0*v0+t)%x;v = (v*v+t)%x;
    while(v0 != v){
        int g = gcd(std::abs(v-v0),x);
        if(g > 1 && g < x) return g;
        v = (v*v+t)%x;v = (v*v+t)%x;
        v0 = (v0*v0+t)%x;
    }
    return x;
}

int ans = 0;

inline void work(int x,int t){
    if(x <= ans || x == 1) return;
    if(isprime(x)) {ans = std::max(ans,x);return;}
    int y = x;while((y = calc(x,t--)) == x);
    while(!(x%y)) x /= y;
    work(x,t);work(y,t);
}

signed main(){
    srand(time(NULL));
    int T;scanf("%lld",&T);
    while(T--){
        int x;scanf("%lld",&x);
        ans = 0;
        work(x,19260817);
        if(ans == x){
            puts("Prime");
            continue;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

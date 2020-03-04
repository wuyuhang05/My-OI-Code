/*
 * Author: RainAir
 * Time: 2019-07-20 19:50:01
 */
#include <unordered_map>
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
std::unordered_map<int,int> S;
int a,p,b;

inline int qpow(int a,int n,int ha){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int bsgs(int a,int p,int b){ // a^x = b(mod p)
    S.clear();b %= p;
    int q = std::ceil(std::sqrt(1.0*p)),t = b;
    FOR(i,0,q){
        t = 1ll*b*qpow(a,i,p)%p;
        S[t] = i;
    }
    a %= p;
    int base = qpow(a,q,p);t = 1;
    FOR(i,1,q){
        t = qpow(a,q*i,p);
        if(S.count(t)){
            int ans = q*i-S[t];
            if(ans < 0) {t = 1ll*t*base%p;continue;}
            return ans;
        }
    }
    return -1;
}

void exgcd(int a,int b,int &x,int &y)  //扩欧
{
    if(!b){
        x=1,y=0;
        return;
    }
    exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-(a/b)*y;
}
int inv(int a,int b)    //逆元
{
    int x,y;
    exgcd(a,b,x,y);
    return (x%b+b)%b;
}

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline int exbsgs(int a,int p,int b){
    if(b == 1 || p == 1) return 0;
    int g = gcd(a,p),k=0,na = 1;
    while(g > 1){
        if(b%g) return -1;
        k++;b /= g;p /= g;na = na*(a/g)%p;
        if(na == b) return k;
        g = gcd(a,p);
    }
    int f = bsgs(a,p,1ll*b*inv(na,p)%p);
    if(f == -1) return -1;
    return f+k;
}

inline void Solve(){
    a %= p;b %= p;
    int ans = exbsgs(a,p,b);
    if(ans == -1) puts("No Solution");
    else printf("%lld\n",ans);
}

signed main(){
    while(~scanf("%lld%lld%lld",&a,&p,&b) && (a+p+b)) Solve();
    return 0;
}

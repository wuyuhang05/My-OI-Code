/*
 * Author: RainAir
 * Time: 2019-08-29 15:52:11
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

const int ha = 1e4;

LL n;

inline void Solve(){
    if(n == 1){
        printf("%04d\n",1);
        return;
    }
    if(n == 2){
        printf("%04d\n",9);
        return;
    }
    LL a,b,c,d,ans = 0;
    a = n+1,b = n,c = n-1,d = n-2;
    if(!(a%4)) a /= 4;
    else if(!(b%4)) b /= 4;
    else if(!(c%4)) c /= 4;
    else d /= 4;
    ans += a*b%ha*c%ha*d%ha;
    a = n+1,b = n,c = n-1;
    /*if(!(a%3)) a /= 3;
    else if(!(b%3)) b /= 3;
    else c /= 3;*/
    (ans += a*b%ha*c%ha) %= ha;
    a = n+1,b = n;
    if(!(a%2)) a /= 2;
    else b /= 2;
    (ans += a*b%ha)%=ha;
    printf("%04lld\n",ans);
}

int main(){
    while(~scanf("%lld",&n)) Solve();
    return 0;
}

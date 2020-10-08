/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-16 19:59:13
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

#define int LL
inline LL S(LL n){
    int res = 0;
    while(n) res += n%10,n /= 10;
    return res;
}

inline LL f(LL n){
    double mn = n/S(n);int ans = n;
    for(int d = 1;d <= n;d *= 10){
        int t = n/d*d+d*10-1;
        double gx = 1.0*t/S(t);
        if(gx < mn){
            mn = gx;
            ans = t;
        }
    }
    return ans;
}

signed main(){
    int n;scanf("%lld",&n);
    LL now = 1;
    while(n--){
        printf("%lld\n",now);
        now = f(now+1);
    }
    return 0;
}

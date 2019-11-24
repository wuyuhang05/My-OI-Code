/*
 * Time: 2019-11-12 20:47:58
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
signed main(){
    int d,k,a,b,t;
    scanf("%lld%lld%lld%lld%lld",&d,&k,&a,&b,&t);
    int ans = b*d;
    ans = std::min(ans,a*d+(d/k)*t+((d%k)?0ll:-t));
    int t1 = d/k;
    ans = std::min(ans,t1*k*a+std::max(0ll,(d/k-1)*t)+(d-t1*k)*b);
    if(d > k) ans = std::min(ans,k*a+(d-k)*b);
    else ans = std::min(ans,a*d);
    printf("%lld\n",ans);
    return 0;
}

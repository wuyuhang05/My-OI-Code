/*
 * Author: RainAir
 * Time: 2019-10-24 08:08:59
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
const int MAXN = 1e5 + 5;
int a[MAXN],n;
int ans = 0;

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,2,n){
        if(a[i-1] < a[i] && a[i] > a[i+1]){
            ans += std::abs(a[i]-std::max(a[i-1],a[i+1]));
            a[i] = std::max(a[i-1],a[i+1]);
        }
        else if(a[i-1] > a[i] && a[i] < a[i+1]){
            ans += std::abs(a[i]-std::min(a[i-1],a[i+1]));
            a[i] = std::min(a[i-1],a[i+1]);
        }
    }
    FOR(i,2,n) ans += std::abs(a[i]-a[i-1]);
    printf("%lld\n",ans);
    return 0;
}


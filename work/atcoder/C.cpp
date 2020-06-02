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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 5e5 + 5;
const int MAX = 1e18;
int n,a[MAXN],mx[MAXN],ans[MAXN];

signed main(){
    scanf("%lld",&n);LL deg0 = 0;
    FOR(i,0,n) scanf("%lld",a+i);
    if(n == 0 && a[0]!= 1){
        puts("-1");
        return 0;
    }
    if(n != 0 && a[0] != 0){
        puts("-1");
        return 0;
    }
    mx[0] = 1;
    FOR(i,1,n){
        mx[i] = (mx[i-1]-a[i-1])*2;
        if(mx[i] < a[i]){
            puts("-1");
            return 0;
        }
        if(mx[i] <= 0){
            puts("-1");
            return 0;
        }
        mx[i] = std::min(mx[i],MAX);
    }
    int res = 0;
    ROF(i,n,0){
        ans[i] = a[i]+ans[i+1];
        ans[i] = std::min(ans[i],mx[i]);
        res += ans[i];
    }
    printf("%lld\n",res);
    return 0;
}

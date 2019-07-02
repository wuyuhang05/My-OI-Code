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

const int MAXN = 2e5 + 5;
LL a[MAXN],n;

int main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i);LL ans = 0;
    FOR(i,1,n-1){
        LL x = a[i],y = a[i+1];
        if(x > y) ans += (x-y)*(n-x+1);
        else ans += (y-x)*x;
    }
    ans += a[n]*(n-a[n]+1);
    printf("%lld\n",ans);
    return 0;
}

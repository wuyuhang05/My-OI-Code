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

const int MAXN = 1e5 + 5;
LL a[MAXN],ans;

int main(){
    int n;scanf("%d",&n);
    FOR(i,1,n){
        LL x,y;scanf("%lld%lld",&x,&y);
        a[i] = x-y;ans += y*n-x;
    }
    std::sort(a+1,a+n+1);std::reverse(a+1,a+n+1);
    FOR(i,1,n){
        ans += i*a[i];
    }
    printf("%lld\n",ans);
    return 0;
}

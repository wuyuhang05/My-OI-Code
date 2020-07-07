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

int main(){
    int T;scanf("%d",&T);
    while(T--){
        LL n;scanf("%lld",&n);
        int cnt = 0;LL t = n;
        while(!(t%2)) cnt++,t >>= 1;
        LL ans = 0;
        FOR(i,cnt+1,64){
            if((1ll<<i) > n) break;
            LL tt = n/(1ll<<i);
            tt = (tt+1)/2;
            ans += tt;
        }
        printf("%lld\n",ans);
    }
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-08-08 19:27:19
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
const int MAXN = 26+5;

inline LL calc(int k,int x,int a){
    return a-k*x >= 0 ? (k-1)*x+std::min(a-k*x,x) : 0;
}

int n,m,a[MAXN];

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i),m = std::max(m,a[i]);
    LL ans = 0ll;
    for(int l = 1,r;l <= m;l = r+1){
        LL sm = 0;r = m;
        FOR(i,1,n){
            LL x = a[i]/(l+1);
            sm += std::max(calc(l,x,a[i]),calc(l,x+1,a[i]));
            if(x) r = std::min(r,a[i]/x-1);
        }
        ans = std::max(ans,sm);
    }
    printf("%lld\n",ans);
    return 0;
}

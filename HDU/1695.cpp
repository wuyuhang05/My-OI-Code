/*
 * Author: RainAir
 * Time: 2019-08-27 17:01:26
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
const int MAXN = 100000+5;

int prime[MAXN],mu[MAXN],cnt;
bool p[MAXN];

inline void prework(int n = MAXN-1){
    mu[1] = 1;
    FOR(i,2,n){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1;
        for(int j = 1;j <= cnt && i*prime[j] <= n;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])){
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = mu[i]*mu[prime[j]];
        }
    }
    FOR(i,1,n) mu[i] += mu[i-1];
}

int cs;

inline void Solve(){
    printf("Case %lld: ",++cs);
    int n,m,d;
    scanf("%*lld%lld%*lld%lld%lld",&n,&m,&d);
    if(!d){
        puts("0");
        return;
    }
    int ans = 0;
    n /= d;m /= d;
    if(n > m) std::swap(n,m);
    for(int l = 1,r = 1;l <= n;l = r+1){
        r = std::min(n/(n/l),m/(m/l));
        ans += (mu[r]-mu[l-1])*(n/l)*(m/l);
    }int t = 0;
    for(int l = 1,r = 1;l <= n;l = r+1){
        r = n/(n/l);
        t += (mu[r]-mu[l-1])*(n/l)*(n/l);
    }
    ans -= t/2;
    printf("%lld\n",ans);
}

signed main(){
    int T;scanf("%lld",&T);prework();
    while(T--) Solve();
    return 0;
}

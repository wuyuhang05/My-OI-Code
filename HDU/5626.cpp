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
#define P std::pair<LL,LL>
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e6 + 5;
LL seed; 
inline LL rand(LL l,LL r){ 
    static LL mo = 1e9 + 7,g = 78125; 
    return l + ((seed *= g) %= mo)%(r-l+1); 
}
int n;
P p[MAXN];LL ans;

inline LL dis(const P &a,const P &b){
    return std::abs(a.fi-b.fi) + std::abs(a.se-b.se);
}

inline void Solve(){
    scanf("%d%lld",&n,&seed);
    FOR(i,1,n)
        p[i].fi = rand(-1000000000,1000000000), 
        p[i].se = rand(-1000000000,1000000000); 
    ans = 0;
    LL max=INT_MIN,min=INT_MAX;
    // x1+y1-x2-y2
    FOR(i,1,n) max = std::max(max,p[i].fi+p[i].se),min = std::min(min,p[i].fi+p[i].se);
    ans = std::max(ans,max-min);
    // -x1+y1+(x2-y2)
    max = INT_MIN,min = INT_MAX;
    FOR(i,1,n) max = std::max(max,-p[i].fi+p[i].se),min = std::min(min,p[i].se-p[i].fi);
    ans = std::max(ans,max-min);max = INT_MIN,min = INT_MAX;
    printf("%lld\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}


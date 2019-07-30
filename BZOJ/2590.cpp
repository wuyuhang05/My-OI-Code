/*
 * Author: RainAir
 * Time: 2019-07-23 14:49:34
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
#define P std::pair<int,int>
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
const int MAXN = 50000+5;
std::priority_queue<int,std::vector<int>,std::greater<int> > q;
int n,k,m;
P a[MAXN];
int ans = 0,now = 0;

inline bool cmp(const P &a,const P &b){
    return a.se == b.se ? a.fi < b.fi : a.se < b.se;
}

signed main(){
    scanf("%lld%lld%lld",&n,&k,&m);k = std::min(k,n);
    FOR(i,1,n) scanf("%lld%lld",&a[i].fi,&a[i].se);
    std::sort(a+1,a+n+1,cmp);
    FOR(i,1,k){
        now += a[i].se;q.push(a[i].fi-a[i].se);
        if(now > m) {printf("%lld\n",i-1);return 0;}
        if(i == n) {printf("%lld\n",n);return 0;}
    }
    ans = k;
    std::sort(a+k+1,a+n+1);
    FOR(i,k+1,n){
        int t=INT_MAX;
        if(!q.empty()) t = q.top();
        if(t < a[i].fi-a[i].se){
            now += t;
            q.pop();q.push(a[i].fi-a[i].se);
            now += a[i].se;
        }
        else now += a[i].fi;
        if(now > m) break;ans++;
    }
    printf("%lld\n",ans);
    return 0;
}

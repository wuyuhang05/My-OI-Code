/*
 * Author: RainAir
 * Time: 2019-09-05 19:33:38
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 2e5 + 5;
int S[MAXN],V;
P a[MAXN];
int n;
std::priority_queue<int> q;

signed main(){
    scanf("%lld%lld",&n,&V);
    FOR(i,1,n){
        int a,b;
        scanf("%lld%lld",&a,&b),S[i] = 1.0*a*V/b;
        ::a[i] = MP(S[i],a);
    }
    std::sort(a+1,a+n+1);std::reverse(a+1,a+n+1);
    int ans = 0,sm = 0;
    FOR(i,1,n){
        q.push(a[i].se);sm += a[i].se;
        while(!q.empty() && a[i].fi < sm) sm -= q.top(),q.pop();
        ans = std::max(ans,(int)q.size());
    }
    printf("%lld\n",ans);
    return 0;
}

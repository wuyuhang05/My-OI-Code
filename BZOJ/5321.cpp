/*
 * Author: RainAir
 * Time: 2019-07-23 13:34:36
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
const int MAXN = 2e5 + 5;
int a[MAXN],n,m,k,d,c[MAXN],cf[MAXN];
std::vector<int> G[MAXN];

inline bool chk(int k){
    cf[0] = cf[n+1] = 0;
    FOR(i,1,n){
        if(a[i] >= k) c[i] = 0;
        else c[i] = std::ceil(1.0*(k-a[i])/(d));
        cf[i] = 0;
    }
    std::priority_queue<int> q;int now = 0,ans = 0;
    FOR(i,1,n){
        now += cf[i];
       // for(auto x:G[i]) q.push(x);
        FOR(j,0,(int)G[i].size()-1) q.push(G[i][j]);
        while(!q.empty() && now < c[i]){
            if(q.top() < i) {q.pop();continue;}
            now++;cf[q.top()+1]--;q.pop();ans++;
        }
        if(now < c[i] || ans > ::k) return false;
    }
    return true;
}

inline void Solve(){
    int mx = INT_MIN,mi = INT_MAX;
    scanf("%lld%lld%lld%lld",&n,&m,&k,&d);
    FOR(i,1,n) G[i].clear(),scanf("%lld",a+i),mi = std::min(mi,a[i]),mx = std::max(mx,a[i]);
    FOR(i,1,m){
        int l,r;scanf("%lld%lld",&l,&r);
        G[l].pb(r);
    }
    int l = mi,r = mx+d*k+233,ans = mi;
    while(l <= r){
        int mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    printf("%lld\n",ans);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

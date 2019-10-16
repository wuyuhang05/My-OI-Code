/*
 * Author: RainAir
 * Time: 2019-08-31 08:27:51
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

const int MAXN = 1e5 + 5;

int pre[MAXN],n,m;
P a[MAXN];

inline void query(int x){
    int l = 0,r = 1;
    int ans = INT_MAX,ansl,ansr,mn = INT_MAX;
    while(r <= n){
        int t = a[r].fi-a[l].fi;
        if(std::abs(t-x) < mn){
            mn = std::abs(t-x);
            ansl = std::min(a[l].se,a[r].se)+1;
            ansr = std::max(a[l].se,a[r].se);
            ans = t;
        }
        if(t < x) r++;
        else if(t > x) l++;
        else break;
        if(l == r) r++;
    }
    printf("%d %d %d\n",ans,ansl,ansr);
}

inline void Solve(){
    FOR(i,1,n){
        int x;scanf("%d",&x);
        pre[i] = pre[i-1]+x;
        a[i] = MP(pre[i],i);
    }
    std::sort(a,a+n+1);
    FOR(i,1,m){
        int x;scanf("%d",&x);
        query(x);
    }
    FOR(i,0,n) pre[i] = 0,a[i].fi = a[i].se = 0;
}

int main(){
    while(~scanf("%d%d",&n,&m) && (n+m)) Solve();
    return 0;
}

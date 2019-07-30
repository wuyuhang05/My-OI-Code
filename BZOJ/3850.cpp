/*
 * Author: RainAir
 * Time: 2019-07-23 15:23:39
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
const int MAXN = 1e5 + 5;
P a[MAXN];
int n;
LL ans;

inline bool cmp(const P &a,const P &b){
    return a.fi*b.se<a.se*b.fi;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",&a[i].fi);
    FOR(i,1,n) scanf("%lld",&a[i].se);
    std::sort(a+1,a+n+1,cmp);int pre = 0;
    FOR(i,1,n){
        pre += a[i].fi;
        ans += pre*a[i].se;
    }
    printf("%lld\n",ans);
    return 0;
}

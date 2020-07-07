/*
 * author: rainair
 * time: 2020-05-28 22:46:54
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
#define db double
#define u unsigned
#define p std::pair<int,int>
#define ll long long
#define pb push_back
#define mp std::make_pair
#define all(x) x.begin(),x.end()
#define clr(i,a) memset(i,a,sizeof(i))
#define for(i,a,b) for(ll i = a;i <= b;++i)
#define rof(i,a,b) for(ll i = a;i >= b;--i)
#define debug(x) std::cerr << #x << '=' << x << std::endl
#define int ll
int h,c,t;
long double f(ll n){
    return 1.0*(h*(n+1)+c*n)/(2*n+1);
}

inline void solve(){
    scanf("%lld%lld%lld",&h,&c,&t);
    int l = 0,r = 1e9,ans = -1;long double ans1 = std::fabs(1.0*(h+c)/2-t);
    while(l <= r){
        ll mid = (l + r) >> 1;
        if(f(mid) <= t) ans = mid,r = mid-1;
        else l = mid+1;
    }
    int res=0;
    if(ans != -1){
        long double mn = 1e9;int ps = 0;
        for(i,std::max(0ll,ans-23),ans+23){
            if(std::fabs(f(i)-t) < mn) mn = std::fabs(f(i)-t),ps = i;
        }
        if(mn < ans1) res = 2*ps+1;
    }
    else res = 2;
    printf("%lld\n",res);
}

signed main(){
    int t;scanf("%lld",&t);
    while(t--) solve();
    return 0;
}

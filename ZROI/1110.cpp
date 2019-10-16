/*
 * Author: RainAir
 * Time: 2019-10-05 09:33:17
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define double long double
const int MAXN = 1000000+5;
int n;

struct Point{
    LL x,y;
    Point(LL x=0,LL y=0) : x(x),y(y) {}

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    LL operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }
}a[MAXN];

inline bool pa(const Point &a,const Point &b){
    return a.y*b.x == a.x*b.y;
}

inline bool pb(const Point &a,const Point &b){
    return a.x*b.x == -a.y*b.y;
}

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline int lcm(int a,int b){
    return a*b/gcd(a,b);
}

//std::set<Node> S;

inline void Solve(){
  //  S.clear();
    scanf("%d",&n);
    FOR(i,1,n){
        Point a,b;
        scanf("%lld%lld%lld%lld",&a.x,&a.y,&b.x,&b.y);
        ::a[i] = a-b;
    }
    int ans = 0;Point base;
    FOR(i,2,n){
        if(!std::abs(a[1]*a[i])) continue;
        if(ans >= 2){
            if(!std::abs(base*a[i])) continue;
            ans = 3;
        }
        if(!ans){
            ans = 2;
            base = a[i];
        }
    }
    if(n == 2 && ans > 1) puts("1");
    else printf("%d\n",ans);
}

int main(){
    int T;
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}


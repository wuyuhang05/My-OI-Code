/*
 * Author: RainAir
 * Time: 2019-10-09 16:56:56
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
#define int LL
const int MAXN = 5000+5;
struct Point{
    int x,y;
    Point(int x=0,int y=0) : x(x),y(y) {}

    bool operator == (const Point &t) const {
        return x == t.x && y == t.y;
    }
}a[MAXN];
int n,L,W;
int ans;

inline void Solve(){
    FOR(i,1,n){
        int l = a[i].x,u = W,d = 0;
        FOR(j,i+1,n){
            int r = a[j].x;
            ans = std::max(ans,std::abs((r-l))*std::abs((u-d)));
            if(a[j].y < a[i].y) d = std::max(d,a[j].y);
            else u = std::min(u,a[j].y); // 强制经过 i
        }
    }
}

signed main(){
    scanf("%lld%lld%lld",&L,&W,&n);
    FOR(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y);
    a[++n] = Point(0,0);a[++n] = Point(0,W);
    a[++n] = Point(L,0);a[++n] = Point(L,W);
    std::sort(a+1,a+n+1,[](const Point &a,const Point &b) -> bool{
              return a.x == b.x ? a.y < b.y : a.x < b.x;
              });
    Solve();
    std::reverse(a+1,a+n+1);
    Solve();
    std::sort(a+1,a+n+1,[](const Point &a,const Point &b) -> bool{
              return a.y < b.y;
              });
    FOR(i,2,n){
        ans = std::max(ans,L*(a[i].y-a[i-1].y));
    }
    printf("%lld\n",ans);
    return 0;
}

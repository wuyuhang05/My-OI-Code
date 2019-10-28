/*
 * Author: RainAir
 * Time: 2019-10-26 17:31:12
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
#define int LL
const int MAXN = 1e5 + 5;
const double EPS = 1e-10;

inline int sgn(double x){
    return std::fabs(x) <= EPS ? 0 : (x < 0 ? -1 : 1);
}

double theta;

struct Point{
    int x,y,y0;
    double x0;

    inline bool operator < (const Point &t) const {
        return !sgn(x0-t.x0) ? y > t.y : sgn(x0-t.x0) > 0;
    }
}a[MAXN];
int n;
double b[MAXN];int sz;
std::vector<int> S;

struct BIT{
    #define lowbit(x) ((x)&(-(x)))
    int tree[MAXN];

    inline void clear(){
        CLR(tree,0);
    }

    inline void add(int pos,int d){
        while(pos){
            tree[pos] += d;
            pos -= lowbit(pos);
        }
    }

    inline int query(int pos){
        int res = 0;
        while(pos < MAXN){
            res += tree[pos];
            pos += lowbit(pos);
        }
        return res;
    }
}bit;

inline bool chk(double theta){
    bit.clear();
    FOR(i,1,n){
        if(sgn(theta-(acos(-1)/2.0))) a[i].x0 = 1.0*a[i].x-1.0*a[i].y/tan(theta);
        else a[i].x0 = a[i].x;
    }
  //  FOR(i,1,n) a[i].x0 = 1.0*a[i].x*sin(theta)-1.0*a[i].y*cos(theta);
    //printf("%.13Lf\n",tan(theta));
    std::sort(a+1,a+n+1);LL ans = 0;
    FOR(i,1,n){
        ans += bit.query(a[i].y0);
        bit.add(a[i].y0,1);
    }
    LL aa = n*(n-1)/2;
    ans = aa-ans;//DEBUG(ans);
    if(aa & 1) return ans >= (aa+1)/2;
    else return ans > aa/2;
}

inline bool chk1(double theta){
    bit.clear();
    FOR(i,1,n){
        if(sgn(theta-(acos(-1)/2.0))) a[i].x0 = 1.0*a[i].x-1.0*a[i].y/tan(theta);
        else a[i].x0 = a[i].x;
    }
  //  FOR(i,1,n) a[i].x0 = 1.0*a[i].x*sin(theta)-1.0*a[i].y*cos(theta);
    //printf("%.13Lf\n",tan(theta));
    std::sort(a+1,a+n+1);LL ans = 0;
    FOR(i,1,n){
        ans += bit.query(a[i].y0);
        bit.add(a[i].y0,1);
    }
    LL aa = n*(n-1)/2;
    ans = aa-ans;//DEBUG(ans);
    if(aa & 1) return ans >= (aa+1)/2;
    else return ans >= aa/2;
}

signed main(){
    freopen("line.in","r",stdin);
    freopen("line.out","w",stdout);
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y),S.pb(a[i].y);
    std::sort(all(S));S.erase(std::unique(all(S)),S.end());
    FOR(i,1,n) a[i].y0 = std::lower_bound(all(S),a[i].y)-S.begin()+1;
    int ts = 100;
    double l = 0,r = acos(-1);
    while(ts--){
        double mid = (l + r) / 2.0;
        if(chk(mid)) l = mid;
        else r = mid;
    }
    if(!((1ll*n*(n-1)/2)&1)){
        double ll = 0,rr = acos(-1);
        ts = 100;
        while(ts--){
            double mid = (ll + rr) / 2.0;
            if(chk1(mid)) ll = mid;
            else rr = mid;
        }
        printf("%.13Lf\n",(ll+rr+l+r)/4.0);
        return 0;
    }
    printf("%.13Lf\n",(l+r)/2.0);
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-11-08 08:40:20
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

const int MAXN = 3000+5;
const double EPS = 1e-9;

inline int sgn(double x){
    return std::fabs(x) <= EPS ? 0 : (x < 0 ? -1 : 1);
}
#define double long double
struct Point{
    double x,y,k;

    Point(double x=0,double y=0) : x(x),y(y) {
        k = atan2(y,x);
    }

    inline Point operator + (const Point &t) const {
        return Point(x+t.x,y+t.y);
    }

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    inline double operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }
}p[MAXN],p0;

inline bool cmp(const Point &x,const Point &y){
     return !sgn(x*y) ? x.x < y.x : sgn(x*y) > 0;
}

std::vector<Point> S;

int n;
double tmp[MAXN];

int main(){
    freopen("a.in","r",stdin);
    scanf("%d",&n);
    FOR(i,1,n) scanf("%Lf%Lf",&p[i].x,&p[i].y),p[i].k = atan2(p[i].y,p[i].x);
    std::sort(p+1,p+n+1,cmp);
    double ans = 0,tans = 0;
    LL tot = 0;
    FOR(i,3,n){
        S.clear();
        FOR(j,1,i-1) S.pb(p[j]-p[i]);
        std::sort(all(S),cmp);
        Point sm = S[0];
//        int smx = S[0].x,smy = S[0].y;
        FOR(j,1,(int)S.size()-1){
            tans += sm*S[j];
//            tans += smx*S[j].y-smy*S[j].x;
//            smx += S[j].x;smy += S[j].y;
            sm = sm+S[j];
        }
    }
    printf("%.1Lf\n",tans/2);
    return 0;
}


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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int n;
const int MAXN = 500+5;
const double EPS = 1e-7;
double f[MAXN][MAXN];

struct Point{
    double x,y;
    Point(){}
    Point(double x,double y) : x(x),y(y) {}

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }
}a[MAXN*MAXN];
int cnt;

inline double dis(const Point &x,const Point &y){
    return std::sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));
}

inline double cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

inline double turn(const Point &a,const Point &b,const Point &p){
    return cross(p-a,p-b);
}

inline bool equ(double x){
    return std::fabs(x) < EPS;
}

struct Seg{
    Point x,y;
    Seg(){}
    Seg(const Point &x,const Point &y) : x(x),y(y) {}
}s[MAXN*MAXN];
int tot;

inline bool pd(const Seg &a,const Seg &b){
    if(turn(a.x,b.x,b.y)*turn(a.y,b.x,b.y) >= 0) return false;
    if(turn(b.x,a.x,a.y)*turn(b.y,a.x,a.y) >= 0) return false;
    return true;
}

inline bool chk(const Seg &t){
    FOR(i,1,tot){
     //   printf("%.2f %.2f %.2f %.2f\n",s[i].x.x,s[i].x.y,s[i].y.x,s[i].y.y);
    //    double a = cross(s[i].x-t.x,s[i].x-t.y),b = cross(s[i].y-t.x,s[i].y-t.y),c = a*b;
        if(pd(s[i],t)) return false;
    }
    return true;
}

inline void Solve(){
    a[cnt = 1] = Point(0,5);tot = 0;
    FOR(i,1,500) FOR(j,1,500) f[i][j] = INT_MAX;
    FOR(i,1,500) f[i][i] = 0.0;
    FOR(i,1,n){
        double x;scanf("%lf",&x);
        FOR(j,1,4){
            double y;scanf("%lf",&y);
            a[++cnt] = Point(x,y);
            if(j == 1) s[++tot] = Seg(Point(x,0),a[cnt]);
            else if(j == 4) s[++tot] = Seg(a[cnt],Point(x,10));
            else if(j == 3) s[++tot] = Seg(a[cnt],a[cnt-1]);
        }
    }
    a[++cnt] = Point(10,5);
  //  FOR(i,1,cnt) printf("%.2f %.2f\n",a[i].x,a[i].y);
  //  DEBUG(chk(Seg(a[1],a[cnt])));
    FOR(i,1,cnt) FOR(j,i+1,cnt){
        if(chk(Seg(a[i],a[j]))){
    //        printf("%.2f %.2f %.2f %.2f\n",a[i].x,a[i].y,a[j].x,a[j].y);
            f[j][i] = f[i][j] = std::min(dis(a[i],a[j]),f[i][j]);
        }
    }
    // FOR(i,1,cnt) {FOR(j,1,cnt) printf("%.2f ",f[i][j]);puts("");}
    FOR(k,1,cnt){
        FOR(i,1,cnt){
            FOR(j,1,cnt){
                f[i][j] = std::min(f[i][j],f[i][k]+f[k][j]);
            }
        }
    }
    printf("%.2f\n",f[1][cnt]);
}

int main(){
    while(~scanf("%d",&n)){
        if(n == -1) return 0;
        Solve();
    }
    return 0;
}

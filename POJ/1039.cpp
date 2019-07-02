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

const int MAXN = 1000+5;
const double EPS = 1e-5;

inline int sgn(double x){
    if(std::fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}


struct Point{
    double x,y;
    Point(){}
    Point(double x,double y) : x(x),y(y) {}

    inline bool operator < (const Point &t) const {
        //return x < t.x;
        return sgn(x-t.x)<0;
    }

    inline Point operator + (const Point &t) const {
        return Point(x+t.x,y+t.y);
    }

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    inline Point operator * (const double &t) const {
        return Point(x*t,y*t);
    }

    inline double operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }

    inline void print(){
        printf("%.3f,%.3f\n",x,y);
    }
}up[MAXN],down[MAXN];

struct Seg{
    Point a,b,vec;
    Seg(){}
    Seg(const Point &a,const Point &b) : a(a),b(b) {
        vec = b-a;
    }
};

inline double cross(const Point &p,const Point &a,const Point &b){
    return (p-a)*(p-b);
}

inline bool xj(const Seg &a,const Seg &b){
    if(sgn(cross(a.a,b.a,b.b))*sgn(cross(a.b,b.a,b.b)) > 0) return false;
    if(sgn(cross(b.a,a.a,a.b))*sgn(cross(b.b,a.a,a.b)) > 0) return false;
    return true;
}

inline bool xj2(const Seg &a,const Seg &b){ // a线段 b直线
    if(sgn(cross(a.a,b.a,b.b))*sgn(cross(a.b,b.a,b.b)) >= 0) return false;
   // if(sgn(cross(b.a,a.a,a.b))*sgn(cross(b.b,a.a,a.b)) >= 0) return false;
    return true;
}

inline bool xj3(const Seg &a,const Seg &b){ // 同上
    if(sgn(cross(a.a,b.a,b.b))*sgn(cross(a.b,b.a,b.b)) > 0) return false;
    return true;
}


inline Point get(const Seg &a,const Seg &b){
    Point u = a.a-b.a;
    double t = b.vec*u/(a.vec*b.vec);
    return a.a + a.vec*t;
}

inline Point mid(const Point &a,const Point &b){
    return Point((a.x+b.x)/2,(a.y+b.y)/2);
}

int n;
std::vector<Point> v;

inline bool cmp(const Point &a,const Point &b){
    return sgn(a.x - b.x) < 0;
}
Point fs[MAXN*2];
int cnt;
inline void Solve(){
    CLR(up,0);CLR(down,0);cnt = 0;bool wj = 0;
    FOR(i,1,n){
        scanf("%lf%lf",&up[i].x,&up[i].y);
        down[i] = Point(up[i].x,up[i].y-1);
        fs[++cnt] = up[i];fs[++cnt] = down[i];
    }
    if(n < 1){
        wj = true;
    }
    double ans = LLONG_MIN;
    FOR(i,1,n){
        FOR(j,1,n){
            if(i == j) continue;
            v.clear();
            Point a = up[i],b = down[j];
            if(!xj3(Seg(up[1],down[1]),Seg(a,b))) continue;
           // v.pb(Point(get(Seg(a,b),Seg(up[1],down[1]))));
            FOR(k,2,n){
                if(xj3(Seg(up[k],up[k-1]),Seg(a,b))) v.pb(get(Seg(up[k],up[k-1]),Seg(a,b)));
                if(xj3(Seg(down[k],down[k-1]),Seg(a,b))) v.pb(get(Seg(down[k],down[k-1]),Seg(a,b)));
            }
            std::sort(all(v),cmp);int top = 0;
            FOR(k,1,(int)v.size()-1){
                Point m = mid(v[k],v[k-1]);bool flag = false;
                FOR(l,2,n){
                    if(sgn(up[l-1].x-m.x) <= 0 && sgn(m.x-up[l].x) <= 0){
                        int a1 = sgn(cross(m,up[l-1],up[l])),a2 = sgn(cross(m,down[l-1],down[l]));
                        if(a1 != 0 && a2 != 0 && !(a1 == -1 && a2 == 1)){
                            flag = true;break;
                        }
                    }
                }
                if(flag) break;
                else top++;
                if(k == (int)v.size()-1){
                    if(xj3(Seg(up[n],down[n]),Seg(a,b))) wj = true,ans = INT_MAX;
                }
            }
            ans = std::max(ans,v[top].x);
        }
    }
    if(wj) puts("Through all the pipe.");
    else printf("%.2f\n",ans);
}

int main(){
    while(scanf("%d",&n) && n) Solve();
    return 0;
}

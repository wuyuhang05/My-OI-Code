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

struct Point{
    double x,y;
    Point(){}
    Point(double x,double y) : x(x),y(y) {}

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    inline double operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }
};

const double EPS = 1e-6;

inline bool equ(double x){
    return std::fabs(x) < EPS;
}
/*
inline double cross(const Point &p,const Point &a,const Point &b){
    return (p-a)*(p-b);
}

inline bool pd(const Point &a,const Point &b,const Point &c,const Point &d){
    int x = turn(a,c,d)*turn(b,c,d),y = turn(c,a,b)*turn(d,a,b);
    if(!equ(x) && x > 0) return false;
    if(!equ(y) && y > 0) return false;
    return true;
}
*/
double cross(Point &o, Point &a, Point &b) {							// 叉积
    return (a.x-o.x)*(b.y-o.y) - (b.x-o.x)*(a.y-o.y); 
}

bool pd(Point p1, Point p2, Point q1, Point q2)
{
    return (
            std::min(p1.x, p2.x) <= std::max(q1.x, q2.x) &&
            std::min(q1.x, q2.x) <= std::max(p1.x, p2.x) &&
            std::min(p1.y, p2.y) <= std::max(q1.y, q2.y) &&
            std::min(q1.y, q2.y) <= std::max(p1.y, p2.y) && /* 跨立实验 */
            cross(p1, q2, q1) * cross(p2, q2, q1) <= 0 &&
            cross(q1, p2, p1) * cross(q2, p2, p1) <= 0  /* 叉积相乘判方向 */
           );
}

Point lu,ld,ru,rd;
Point S,T;

inline bool in(const Point &p){
    return p.x >= lu.x && p.x <= rd.x && p.y >= rd.y && p.y <= lu.y;
}

inline void Solve(){
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&S.x,&S.y,&T.x,&T.y,&lu.x,&lu.y,&rd.x,&rd.y);
    if(lu.x > rd.x) std::swap(lu.x,rd.x);
    if(lu.y < rd.y) std::swap(lu.y,rd.y);
//    DEBUG(in(S));DEBUG(in(T));
  //  DEBUG(S.x);DEBUG(S.y);DEBUG(lu.x);DEBUG(rd.x);DEBUG(rd.y);DEBUG(lu.y);
    ld = Point(lu.x,rd.y);ru = Point(rd.x,lu.y);
    //if((in(S) && in(T)) || pd(lu,ld,S,T) || pd(ld,rd,S,T) || pd(rd,ru,S,T) || pd(ru,lu,S,T)) puts("T");
    if((in(S) && in(T)) || pd(lu,rd,S,T) || pd(ld,ru,S,T)) puts("T");
    else puts("F");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

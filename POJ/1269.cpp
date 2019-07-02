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

const double EPS = 1e-6;

struct Point{
    double x,y;
    Point(){}
    Point(double x,double y) : x(x), y(y) {}

    inline Point operator + (const Point &t) const {
        return Point(x+t.x,y+t.y);
    }

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    inline double operator * (const Point &t) const {
        return x*t.x+y*t.y;
    }

    inline Point operator * (const double t) const {
        return Point(x*t,y*t);
    }

    inline void read(){
        scanf("%lf%lf",&x,&y);
    }
};

inline double cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

inline bool equ(double x){
    return std::fabs(x) <= EPS;
}

struct Line{
    Point S,T,vec;
    inline void read(){
        S.read();T.read();
        vec = T-S;
    }
}l1,l2;

inline Point intersect(const Line &a,const Line &b){
    Point u = (a.S-b.S);
    double t = cross(b.vec,u)/cross(a.vec,b.vec);
    return a.S + a.vec*t;
}

inline void Solve(){
    l1.read();l2.read();
    if(equ(cross(l1.vec,l2.vec))){
        if(equ(cross(l2.S-l1.S,l2.S-l1.T))){
            puts("LINE");return;
        }
        else{
            puts("NONE");return;
        }
    }
    else{
        Point ans = intersect(l1,l2);
        printf("POINT %.2f %.2f\n",ans.x,ans.y);
    }
}

int main(){
    puts("INTERSECTING LINES OUTPUT");
    int T;scanf("%d",&T);
    while(T--) Solve();
    puts("END OF OUTPUT");
    return 0;
}

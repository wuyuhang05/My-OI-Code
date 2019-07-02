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

const double EPS = 1e-8;
const int MAXN = 100+5;

struct Point{
    double x,y;
    Point(){}
    Point(double x,double y) : x(x),y(y) {}

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }
};

inline double cross(const Point &a,const Point &b){
   // DEBUG(a.x);DEBUG(a.y);DEBUG(b.x);DEBUG(b.y);
    return a.x*b.y-a.y*b.x;
}

struct Seg{
    Point a[2];
    Seg(){}
    Seg(const Point &aa,const Point &b){
        a[0] = aa;a[1] = b;
    }
}s[MAXN];

int n;

inline double dis(const Point &a,const Point &b){
    return std::sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

inline bool chk(Seg q){
    if(dis(q.a[0],q.a[1]) < EPS) return false;
    FOR(i,1,n){
        // DEBUG(cross(s[i].a[0]-q.a[0],s[i].a[0]-q.a[1]));DEBUG(cross(s[i].a[1]-q.a[1],s[i].a[1]-q.a[1]));
        if(cross(s[i].a[0]-q.a[0],s[i].a[0]-q.a[1])*cross(s[i].a[1]-q.a[0],s[i].a[1]-q.a[1]) > EPS) return false;
    }
    return true;
}

inline void Solve(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%lf%lf%lf%lf",&s[i].a[0].x,&s[i].a[0].y,&s[i].a[1].x,&s[i].a[1].y);
    if(n == 1){
        puts("Yes!");return;
    }
    FOR(i,1,n){
        FOR(j,i+1,n){
            FOR(ii,0,1) FOR(jj,0,1) if(chk(Seg(s[i].a[ii],s[j].a[jj]))) {puts("Yes!");return;}
        }
    }
    puts("No!");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

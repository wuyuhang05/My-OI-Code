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

const int MAXN = 10000+5;
const double EPS = 1e-6;

struct Point{
    int x,y;
    Point(){}
    Point(int x,int y) : x(x),y(y) {}

    Point operator + (const Point &t) const {
        return Point(x+t.x,y+t.y);
    }

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    bool operator < (const Point &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }
}p[MAXN]; 

struct Poly{
    Point p[4];
    Poly(){}
    Poly(const Point &a,const Point &b,const Point &c,const Point &d){
        p[0] = a,p[1] = b,p[2] = c,p[3] = d;
    }
}s[MAXN];

inline double cross(const Point &a,const Point &b){
    return a.x*b.y-a.y*b.x;
}

inline int sgn(double x){
    if(std::fabs(x) <= EPS) return 0;
    return x > 0 ? 1 : -1;
}

inline bool chk(const Poly &a,const Point x){
    FOR(i,0,3){
        int now = i,nxt = (now+1)%4;
        if(sgn(cross(a.p[now]-x,a.p[nxt]-x)) > 0) return false;
    }
    return true;
}

int ans[MAXN],n,m;
Point lu,rd,ld,ru;

int main(){
    while(~scanf("%d",&n)){
        if(n == 0) return 0;
        scanf("%d%d%d%d%d",&m,&lu.x,&lu.y,&rd.x,&rd.y);
        ld = Point(lu.x,rd.y);ru = Point(rd.x,lu.y);CLR(ans,0);
        FOR(i,1,n) scanf("%d%d",&p[i].x,&p[i].y);
        std::sort(p+1,p+n+1);
        s[0] = Poly(ld,lu,Point(p[1].x,lu.y),Point(p[1].y,ld.y));
        FOR(i,2,n){
            s[i-1] = Poly(Point(p[i-1].y,ld.y),Point(p[i-1].x,lu.y),Point(p[i].x,lu.y),Point(p[i].y,ld.y));
        }
        s[n] = Poly(Point(p[n].y,ld.y),Point(p[n].x,lu.y),ru,rd);
       /* FOR(i,0,n){
            printf("%d:\n",i);
            FOR(j,0,3) printf("%d %d\n",s[i].p[j].x,s[i].p[j].y);
        }*/
        FOR(i,1,m){
            Point a;scanf("%d%d",&a.x,&a.y);
            FOR(j,0,n){
                if(chk(s[j],a)){
                    ans[j]++;break;
                }
            }
        }
        FOR(i,0,n) printf("%d: %d\n",i,ans[i]);puts("");
    }
    return 0;
}

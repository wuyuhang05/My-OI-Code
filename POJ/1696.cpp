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

const int MAXN = 50+5;
const double EPS = 1e-6;
int n;

struct Point{
    double x,y;int num;
    Point(){}
    Point(double x,double y,int num=0) : x(x),y(y),num(num) {}

    inline Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    inline double operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }
}a[MAXN];

inline double dot(const Point &a,const Point &b){
    return a.x*b.x+a.y*b.y;
}

inline double dis(const Point &a,const Point &b){
    return dot((a-b),(a-b));
}

inline int sgn(double x){
    if(std::fabs(x) < EPS) return 0;
    return x > 0 ? 1 : -1;
}

inline double cross(const Point &k,const Point &x,const Point &y){
    return (k-x)*(k-y);
}

Point tmp;

inline bool cmp(const Point &x,const Point &y){
    double t = cross(y,tmp,x);
    if(sgn(t) == 0) return dis(tmp,x) < dis(tmp,y);
    return t > 0;
    if(t < 0) return false;
    return true;
}

inline void Solve(){
    scanf("%d",&n);a[0] = Point(0,INT_MAX,0);
    FOR(i,1,n) scanf("%d%lf%lf",&a[i].num,&a[i].x,&a[i].y),a[0].y = std::min(a[0].y,a[i].y);
    FOR(i,0,n){
        tmp = a[i];std::sort(a+i+1,a+1+n,cmp);
       // DEBUG(a[i+1].x);DEBUG(a[i+1].y);
       // if(cross(a[i+1],a[i],a[i-1]) < 0) break;
       // ans++;
    }
    int ans = n;
    printf("%d ",ans);
    FOR(i,1,ans) printf("%d ",a[i].num);puts("");
    //printf("%d\n",ans);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

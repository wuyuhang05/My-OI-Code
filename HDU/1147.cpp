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

const int MAXN = 100000+5;

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
        return x*t.y-y*t.x;
    }
};

inline double cross(const Point &p,const Point &a,const Point &b){
    return (p-a)*(p-b);
}

struct Seg{
    Point a,b;
    Seg(){}
    Seg(const Point &a,const Point &b) : a(a),b(b) {}
}l[MAXN];

inline bool pd(const Seg &a,const Seg &b){
    if(cross(a.a,b.a,b.b)*cross(a.b,b.a,b.b) > 0) return false;
    if(cross(b.a,a.a,a.b)*cross(b.b,a.a,a.b) > 0) return false;
    return true;
}

int n;
std::vector<int> ans;

inline bool chk(int k,const Seg &a){
    FOR(i,k+1,n){
        Seg x = l[i];
        if(pd(x,a)) return false;
    }
    return true;
}

inline void Solve(){
    FOR(i,1,n) scanf("%lf%lf%lf%lf",&l[i].a.x,&l[i].a.y,&l[i].b.x,&l[i].b.y);
    ans.clear();
    FOR(i,1,n) if(chk(i,l[i])) ans.pb(i);
    printf("Top sticks: ");
    FOR(i,0,(int)ans.size()-1){
        printf("%d",ans[i]);
        if(i != (int)ans.size()-1) printf(", ");
    }
    puts(".");
}

int main(){
    while(~scanf("%d",&n) && n) Solve();
    return 0;
}



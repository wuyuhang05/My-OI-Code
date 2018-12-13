#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200000+5;
const double EPS = 1e-9;

inline bool equ(double x,double y){
    return std::fabs(x-y) < EPS;
}

struct Point{
    double x,y;

    Point() {}
    Point(double x,double y) : x(x),y(y) {}

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    double operator * (const Point &t) const { // 有向三角形构成的面积
        return x*t.y - y*t.x;
    }

    bool operator < (const Point &t) const {
        return equ(x,t.x) ? y < t.y : x < t.x;
    }

    bool operator == (const Point &t) const {
        return equ(x,t.x) && equ(y,t.y);
    }

    double len(){ // 到原点的距离
        return std::sqrt(x*x+y*y);
    }
}p[MAXN],S[MAXN];

int top;

bool cmp(const Point &a,const Point &b){
    return std::fabs((a-p[1])*(b-p[1])) < EPS ? (a-p[1]).len() < (b-p[1]).len() : (a-p[1])*(b-p[1]) > 0;
    // 同一直线比较长度否则比较谁在右侧
}

int N;
int w[MAXN],sum[MAXN];

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",w+i);
    FOR(i,1,N) sum[i] = sum[i-1] + w[i];
    FOR(i,1,N) p[i] = Point(1.0*sum[i]/w[i],sum[i]);
    std::sort(p+1,p+N+1); // 最小的 p
    std::sort(p+2,p+N+1,cmp); // 极角排序
    N = std::unique(p+1,p+N+1)-(p+1);
    FOR(i,1,N){
        while(top > 1 && (p[i]-S[top-1])*(S[top-1]-S[top-2]) > 0) // 这个点在逆时针方向弹掉
            top--;
        S[top++] = p[i];
    }
    double ans = 0.0;
    FOR(i,0,top-1){
        ans += S[i]*S[(i+1)%top];
    }
    printf("%.5f",ans/2.0);
    return 0;
}
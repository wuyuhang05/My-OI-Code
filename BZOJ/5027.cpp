/*
 * Author: RainAir
 * Time: 2019-07-18 14:33:25
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1,y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y,y = t-(a/b)*y;
    return g;
}

//int g,a,b,c,x1,x2,y1,y2,x0,y0;
//ax+by = -c
signed main(){
    int g,a,b,c,x1,x2,y1,y2,x0,y0;
    scanf("%lld%lld%lld%lld%lld%lld%lld",&a,&b,&c,&x1,&x2,&y1,&y2);c = -c;
    if(!a && !b){
        printf("%lld\n",c == 0 ? (x2-x1+1)*(y2-y1+1) : 0);
        return 0;
    }
    if(!a){
        printf("%lld\n",(c%b || (c/b < y1 || c/b > y2)) ? 0 : (x2-x1+1));
        return 0;
    }
    if(!b){
        printf("%lld\n",(c%a || (c/a < x1 || c/a > x2)) ? 0 : (y2-y1+1));
        return 0;
    }
    g = exgcd(a,b,x0,y0);
    if(c%g){
        puts("0");return 0;
    }
    b = b/g;a = -a/g;
    x0 = x0*c/g;y0 = y0*c/g;
    int xl,xr,yl,yr;
    if(b < 0) std::swap(x1,x2);
    xl = std::ceil(1.0*(x1-x0)/b),xr = std::floor(1.0*(x2-x0)/b);
    if(a < 0) std::swap(y1,y2);
    yl = std::ceil(1.0*(y1-y0)/a),yr = std::floor(1.0*(y2-y0)/a);
    printf("%lld\n",std::max(0ll,std::min(xr,yr)-std::max(xl,yl)+1));
    return 0;
}

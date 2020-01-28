/*
 * Time: 2019-11-27 15:35:41
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;
#define int LL
struct Point{
    int x,y,id;
    Point(int x=0,int y=0) : x(x),y(y) {}

    Point operator - (const Point &t) const {
        return Point(x-t.x,y-t.y);
    }

    LL operator * (const Point &t) const {
        return x*t.y-y*t.x;
    }
}a[MAXN],S[MAXN];
int tp = 0;
std::vector<int> ans;

inline bool cmp(const Point &x,const Point &y){
    return x.x == y.x ? x.y < y.y : x.x < y.x;
}

int n;

signed main(){
    freopen("a.in","r",stdin);
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y),a[i].id = i,a[i].x = -a[i].x;
    std::sort(a+1,a+n+1,cmp);
    FOR(i,1,n){
        if(i < n && a[i].x == a[i+1].x) continue;
        while(tp >= 2 && (S[tp]-S[tp-1])*(a[i]-S[tp]) >= 0) tp--;
        S[++tp] = a[i];
    }
    FOR(i,1,tp) ans.pb(S[i].id);
    std::sort(all(ans));
    FOR(i,0,tp-1) printf("%lld ",ans[i]);puts("");
    return 0;
}

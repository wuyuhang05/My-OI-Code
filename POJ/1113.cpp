#include<iostream>
#include<cstdio>
#include<algorithm>
#include <cmath>
#include<vector>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
const int MAXN = 2e5 + 5;
const double pi = acos(-1);

struct Node{
    int x,y;

    Node(int x=0,int y=0) : x(x),y(y) {}

    inline Node operator - (const Node &t) const {
        return Node(x-t.x,y-t.y);
    }

    inline int operator * (const Node &t) const {
        return x*t.y-y*t.x;
    }

    bool operator < (const Node &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }

    inline double dist(){
        return std::sqrt(1.0*x*x+1.0*y*y);
    }
}a[MAXN];
std::vector<Node> top,bot;
int n;

inline void andrew(){
    std::sort(a+1,a+n+1);
    FOR(i,1,n){
        while(bot.size() > 1 && (bot.back()-bot[bot.size()-2])*(a[i]-bot.back()) <= 0) bot.pop_back();
        bot.pb(a[i]);
    }
    ROF(i,n,1){
        while(top.size() > 1 && (top.back()-top[top.size()-2])*(a[i]-top.back()) <= 0) top.pop_back();
        top.pb(a[i]);
    }
    std::reverse(all(top));
}

int main(){
    int d;scanf("%d%d",&n,&d);
    FOR(i,1,n) scanf("%d%d",&a[i].x,&a[i].y);
    andrew();
    double ans = 2*pi*d;
    FOR(i,1,(int)bot.size()-1) ans += (bot[i]-bot[i-1]).dist();
    FOR(i,1,(int)top.size()-1) ans += (top[i]-top[i-1]).dist();
    printf("%d\n",(int)(ans+0.5));
    return 0;
}

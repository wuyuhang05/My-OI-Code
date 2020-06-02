#include<bits/stdc++.h>

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
#define int LL
const int MAXN = 2e5 + 5;

int n,m;

struct Node{
    int x,y;
    Node(int x=0,int y=0) : x(x),y(y) {}

    Node operator - (const Node &t) const {
        return Node(x-t.x,y-t.y);
    }

    int operator * (const Node &t) const {
        return x*t.y-y*t.x;
    }

    bool operator < (const Node &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }
}a[MAXN];
std::vector<Node> top,bot;

inline void andrew(){
    std::sort(a+1,a+n+1);
    FOR(i,1,n){
        if(i != 1 && a[i].x == a[i-1].x) continue;
        while(bot.size() > 1 && (bot[bot.size()-1]-bot[bot.size()-2])*(a[i]-bot[bot.size()-1]) <= 0) bot.pop_back();
        bot.pb(a[i]);
    }
    ROF(i,n,1){
        if(i != n && a[i].x == a[i+1].x) continue;
        while(top.size() > 1 && (top[top.size()-1]-top[top.size()-2])*(a[i]-top[top.size()-1]) <= 0) top.pop_back();
        top.pb(a[i]);
    }
    std::reverse(all(top));
}

inline bool query(Node p){
    if(p.x < top[0].x || p.x > top.back().x) return false;
    if(p.x < bot[0].x || p.x > bot.back().x) return false;
    if(p.x == bot[0].x && p.y < bot[0].y) return false;
    if(p.x == bot.back().x && p.y < bot.back().y) return false;
    if(p.x == top[0].x && p.y > top[0].y) return false;
    if(p.x == top.back().x && p.y > top.back().y) return false;
    int up = std::upper_bound(all(top),Node(p.x,1e9))-top.begin()-1;
    int down = std::upper_bound(all(bot),Node(p.x,1e9))-bot.begin()-1;
//    DEBUG(top[0].x);DEBUG(top[0].y);
//    DEBUG(bot[0].x);DEBUG(bot[0].y);
//  DEBUG(up);
    if(up+1 < top.size()) if((top[up+1]-top[up])*(p-top[up]) > 0) return false;
    if(down+1 < bot.size()) if((bot[down+1]-bot[down])*(p-bot[down]) < 0) return false;
    return true;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld%lld",&a[i].x,&a[i].y);
    andrew();scanf("%lld",&m);int ans = 0;
    while(m--){
        int x,y;scanf("%lld%lld",&x,&y);
        ans += query(Node(x,y));
//        if(query(Node(x,y))) DEBUG(x),DEBUG(y);
    }
    printf("%lld\n",ans);
    return 0;
}

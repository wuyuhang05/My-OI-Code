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
#define db double
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
const int MAXN = 1e5 + 5;
const int MAXM = 300+5;

int BLO;
int bel[MAXN];
int add[MAXN],b[MAXN],tx[MAXN];
int n,a[MAXN];

struct Node{
    int x,y;
    Node(int x=0,int y=0) : x(x),y(y) {}
};

inline bool pd(const Node &a,const Node &b,const Node &c,const Node &d){
    return (a.y-b.y)*(c.x-d.x) <= (a.x-b.x)*(c.y-d.y);
}

std::deque<Node> tb[MAXM];

inline void rebuild(int x){
    tb[x].clear();
    ROF(i,x*BLO,(x-1)*BLO+1){
        Node p(-(i-1),b[i]);
        while(tb[x].size() >= 2 && pd(p,tb[x].back(),tb[x].back(),tb[x][tb[x].size()-2])) tb[x].pop_back();
        tb[x].pb(p);
    }
}

inline int calc(int x){
    return add[bel[x]]+(x-1)*tx[bel[x]]+b[x];
}

inline int calcc(int x){
    while(tb[x].size() >= 2 && calc(-tb[x][0].x+1) >= calc(-tb[x][1].x+1)) tb[x].pop_front();
    return calc(-tb[x][0].x+1);
}

inline int query(int l,int r){
    int res = 1e18;
    if(bel[l] == bel[r]){
        FOR(i,l,r) res = std::min(res,calc(i));
        return res;
    }
    FOR(i,l,bel[l]*BLO) res = std::min(res,calc(i));
    FOR(i,(bel[r]-1)*BLO+1,r) res = std::min(res,calc(i));
    FOR(i,bel[l]+1,bel[r]-1) res = std::min(res,calcc(i));
    return res;
}

inline void modify1(int l,int r,int d){
    if(bel[l] == bel[r]){
        FOR(i,l,r) b[i] += d;
        rebuild(bel[l]);return;
    }
    FOR(i,l,bel[l]*BLO) b[i] += d;rebuild(bel[l]);
    FOR(i,(bel[r]-1)*BLO+1,r) b[i] += d;rebuild(bel[r]);
    FOR(i,bel[l]+1,bel[r]-1) add[i] += d;
}

inline void modify2(int l,int r,int d){
    if(bel[l] == bel[r]){
        FOR(i,l,r) b[i] += (i-1)*d;
        rebuild(bel[l]);return;
    }
    FOR(i,l,bel[l]*BLO) b[i] += (i-1)*d;rebuild(bel[l]);
    FOR(i,(bel[r]-1)*BLO+1,r) b[i] += (i-1)*d;rebuild(bel[r]);
    FOR(i,bel[l]+1,bel[r]-1) tx[i] += d;
}

inline void update(int p,int d){
    int x = bel[p];
    FOR(i,(x-1)*BLO+1,x*BLO) b[i] += add[x]+(i-1)*tx[x];
    tx[x] = add[x] = 0;b[p] = d;
    rebuild(x);
}

int mx[MAXN];
signed main(){
    scanf("%lld",&n);FOR(i,1,n) scanf("%lld",a+i),mx[i] = std::max(mx[i-1],a[i]);
    BLO = std::sqrt(1.0*(n+1));
//    BLO  = 300;
    FOR(i,1,n+1) bel[i] = (i-1)/BLO+1;
    FOR(i,2,n+1) b[i] = 1e16;
    FOR(i,1,bel[n+1]) rebuild(i);
    FOR(i,1,n){
        if(mx[i] == a[i]){
            modify1(1,n+1,a[i]);
            int t = query(1,n+1);
            update(mx[i]+1,t);
        }
        else{
            int t = query(1,a[i]+1);
            update(a[i]+1,t+a[i]);
       //     DEBUG(calc(4));
     //       exit(0);
            modify2(a[i]+2,n+1,1);
            modify1(1,a[i],mx[i]);
        }
//        FOR(i,1,n+1) printf("%lld ",query(i,i));puts("");
    }
    printf("%lld\n",query(1,n+1)-n*(n+1)/2);
    return 0;
}

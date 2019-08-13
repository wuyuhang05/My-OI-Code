/*
 * Author: RainAir
 * Time: 2019-08-10 23:47:54
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
inline int lca(int x,int y){
    while(x != y){
        if(x < y) std::swap(x,y);
        x >>= 1;
    }
    return x;
}

inline int find(int x){
    int lst = x&1;
    while(lst == (x&1)) x >>= 1;
    return std::max(1ll,x>>1);
}

inline void Solve(){
    LL a,b;scanf("%lld%lld",&a,&b);
    ++a;++b;int t = lca(a,b);int ans = 0;
    int p1=0,p2=0;
    while(find(a) > t) a = find(a),ans++;
    if(a == t) p1 = -1;
    else if(a>>1 == t) p1 = 0;
    else{
        int tmp = a&1;p1 = 1;
        while(a != t) p1 &= (tmp==(a&1)),a >>= 1;
    }
    while(find(b) > t) b = find(b),ans++;
    if(b == t) p2 = -1;
    else if(b>>1 == t) p2 = 0;
    else{
        int tmp = b&1;p2 = 1;
        while(b != t) p2 &= (tmp==(b&1)),b >>= 1;
    }
    if(p1 != -1 && p2 != -1) ans += p1|p2;
    printf("%lld\n",ans);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

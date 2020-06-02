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
inline int pd(int x){
    while(!(x%2)) x /= 2;
    while(!(x%5))x /= 5;
    return x;
}
const int mu[] = {0,1,-1,-1,0,-1,1,-1,0,0,1,-1,0};

inline int f(int n,int m){
    int res= 0;
    FOR(d,1,10){
        if(10%d) continue;
        if(mu[d] == 0) continue;
        int t = 0,nn = n/d;
        for(int l = 1,r;l <= m/d;l = r+1){
            r = nn/(nn/l);
            t += (nn/l)*(r-l+1);
        }
        res += t*mu[d];
    }
    return res;
}

signed main(){
    int n;scanf("%lld",&n);LL ans = 0;
    int pw2 = 1;int cnt = 0;
    FOR(x,0,40){
        if(pw2 > n) break;
        int pw5 = 1;
        FOR(y,0,20){
            if(pw2*pw5 > n) break;
            ans += f(n,n/(pw2*pw5));
            pw5 = 1ll*pw5*5;
        }
        pw2 = 1ll*pw2*2;
    }
    printf("%lld\n",ans);
    return 0;
}

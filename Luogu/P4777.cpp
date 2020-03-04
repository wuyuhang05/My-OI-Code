/*
 * Author: RainAir
 * Time: 2019-07-18 13:38:29
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
const int MAXN = 1e5 + 5;
int aa[MAXN],bb[MAXN];
int n;

inline int qmul(int a,int b,int ha){
    int res = 0;
    while(b){
        if(b & 1) res = (res+a)%ha;
        a = (a+a)%ha;
        b >>= 1;
    }
    return res;
}

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1,y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}
int x,y;
inline int excrt(){
    int ans = aa[1],M = bb[1];// M = lcm
    FOR(i,2,n){
        int a = M,b = bb[i],c = (aa[i]-ans%b+b)%b;// 这里 ax=c(mod b)
        int g = exgcd(a,b,x,y),bg = b/g;
        if(c%g) return -1;
        x = qmul(x,c/g,bg);
        ans = ans+M*x;
        M *= bg;
        ans = (ans+M)%M; // 这里已经是新意义下的了
    }
    return (ans+M)%M;
}

signed main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld%lld",bb+i,aa+i);
    printf("%lld\n",excrt());
    return 0;
}

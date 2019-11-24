/*
 * Time: 2019-11-13 21:56:36
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
#define int LL
const int MAXN = 15+1;

int n,x,y;
int p[MAXN],a[MAXN];

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}

bool use[MAXN];
int M;

inline int excrt(){
    int ans = 0;M = 1;
    FOR(i,1,n+1){
        if(!use[i]) continue;
        int a = M,b = p[i],c = (::a[i]-ans+b)%b,x,y;
        int g = exgcd(a,b,x,y),bg = b/g;
        if(c%g) return -1;
        x = (x*c/g)%bg;
        ans = ans+M*x;
        M *= bg;
        ans = (ans+M)%M;
    }
    return ans;
}

inline int calc(int S,int l){
    FOR(i,0,n-1) use[i+1] = (S>>i)&1;
    use[n+1] = 1;
    int mn = excrt();
    if(mn > l) return 0;
    return 1+(l-mn)/M;
}

int pc[(1<<MAXN)+3],cs;

inline void Solve(){
    scanf("%lld%lld%lld",&n,&x,&y);
    FOR(i,1,n) scanf("%lld%lld",p+i,a+i);
    p[n+1] = 7;a[n+1] = 0;
    int ans = 0;
    FOR(S,0,(1<<n)-1){
        int gx = calc(S,y)-calc(S,x-1);
//        DEBUG(gx);
        ans += ((pc[S]&1) ? -1 : 1)*gx;
    }
    printf("Case #%lld: %lld\n",++cs,ans);
}

signed main(){
    pc[0] = 0;
    FOR(i,1,(1<<MAXN)) pc[i] = pc[i>>1] + (i&1);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

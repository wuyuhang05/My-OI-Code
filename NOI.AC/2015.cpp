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
const int MAXN = 2e6 + 5;
const int ha = 1e9 + 7;

struct Node{
    int t,d,x;// 时间 周期 坐标
    Node(int t=0,int d=0,int x=0) : t(t),d(d),x(x) {}
    bool operator < (const Node &_) const {
        return t < _.t;
    }
}a[MAXN];
int t[MAXN],x[MAXN],y[MAXN];
int n,l;
int fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int calc(int c){
    FOR(i,1,n) a[i].x -= a[i].d*c;
    a[0].t = 0;a[0].x = 0;
    a[n+1].t = l;a[n+1].x = c;
    bool flag = 1;
    int ans = 1;
    FOR(i,0,n){
        if(a[i].d == a[i+1].d && a[i].t == a[i+1].t && a[i].x != a[i+1].x){flag = 0;break;}
        if(a[i].d == a[i+1].d && a[i].t == a[i+1].t && a[i].x == a[i+1].x) continue;
        int x = a[i+1].x-a[i].x,t = a[i+1].t-a[i].t;
        if((x+t)%2){flag = 0;break;}
        int xx = (x+t)/2,yy = t-xx;
      //  if(i == 3) DEBUG(xx),DEBUG(yy);
        if(xx < 0 || yy < 0){flag = 0;break;}
        ans = 1ll*ans*C(xx+yy,xx)%ha;
    }
    FOR(i,1,n) a[i].x += a[i].d*c;
    return ans*flag;
}

inline int solve(){
    int L = -l,R = l,ans = 0;
    std::sort(a+1,a+n+1);
    FOR(i,1,n-1){
        int p = a[i+1].d-a[i].d,t = a[i+1].t-a[i].t,x = a[i+1].x-a[i].x;
        if(p > 0){
            L = std::max(L,(LL)std::ceil(1.0*(x-t)/p));
            R = std::min(R,(x+t)/p);
        }
        if(p < 0){
            L = std::max(L,(LL)std::ceil(1.0*(x+t)/p));
            R = std::min(R,(x-t)/p);
        }
    }
    FOR(i,L,R) (ans += calc(i)) %= ha;
    return ans;
}

signed main(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    scanf("%lld%lld",&n,&l);
    FOR(i,1,n) scanf("%lld%lld%lld",t+i,x+i,y+i);
    FOR(i,1,n) a[i] = Node(t[i]%l,t[i]/l,x[i]-y[i]);
    int ansl = solve();
    FOR(i,1,n) a[i] = Node(t[i]%l,t[i]/l,x[i]+y[i]);
    int ansr = solve();
    printf("%lld\n",1ll*ansl*ansr%ha);
    return 0;
}

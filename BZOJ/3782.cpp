/*
 * Author: RainAir
 * Time: 2019-08-20 19:17:54
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
const int MAXN = 2000+5;
struct Node{
    int x,y;

    bool operator < (const Node &t) const {
        return x == t.x ? y < t.y : x < t.x;
    }
}a[MAXN];
int n,m,t,p;
std::vector<std::pair<int,int> > dec;

inline int qpow(int a,int n,int ha){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1)res = res*a;
        a = a*a;
        n >>= 1;
    }
    return res;
}

inline void fg(){
    int q = std::sqrt(1.0*p);int t = p;
    FOR(i,2,q){
        if(!(t%i)){
            int cnt = 0;
            while(!(t%i)) t /= i,cnt++;
            dec.pb(MP(i,cnt));
        }
    }
    if(t != 1) dec.pb(MP(t,1));
}

const int MAXM = 2e6 + 5;
int fac[MAXM],inv[MAXM];
int f[MAXN],P;

inline int C(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    if(n < P && m < P) return 1ll*fac[n]*inv[m]%P*inv[n-m]%P;
    return C(n%P,m%P)*C(n/P,m/P)%P;
}

inline int solve(int p,int e){
    P = qpow(p,e);
    fac[0] = 1;FOR(i,1,P-1) fac[i] = 1ll*fac[i-1]*i%P;
    inv[P-1] = qpow(fac[P-1],P-2,P);
    ROF(i,P-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%P;
    CLR(f,0);
    FOR(i,1,t){
        f[i] = C(a[i].x+a[i].y,a[i].x);
        FOR(j,1,i-1){
            if(a[j].x <= a[i].x && a[j].y <= a[i].y){
                int dx = a[i].x-a[j].x,dy = a[i].y-a[j].y;
                f[i] = (f[i]-C(dx+dy,dx)*f[j]%P+P)%P;
             //   assert(f[i] >= (C(dx+dy,dx)*f[j]));
            }
        }
    }
    return f[t];
}

int ans[MAXN];

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1,y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}

inline int ginv(int a,int p){
    int x,y;exgcd(a,p,x,y);
    return (x+p)%p;
}

int sz;

inline int CRT(){
    int res = 0;
    FOR(i,1,sz){
        int pp = qpow(dec[i-1].fi,dec[i-1].se);
        int Mi = p/pp,invM = ginv(Mi,pp);
        (res += Mi*invM*ans[i]%p) %= p;
    }
    return (res+p)%p;
}

signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&t,&p);
    FOR(i,1,t) scanf("%lld%lld",&a[i].x,&a[i].y);
    a[++t] = (Node){n,m};std::sort(a+1,a+t+1);
    fg();sz = dec.size();
    FOR(i,1,sz) ans[i] = solve(dec[i-1].fi,dec[i-1].se);
    printf("%lld\n",CRT());
    return 0;
}

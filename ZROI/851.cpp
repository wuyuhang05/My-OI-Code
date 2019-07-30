/*
 * Author: RainAir
 * Time: 2019-07-21 12:39:06
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

inline int qmul(int x,int y,int p){
    LL k = (LL)((1.0L*x*y)/(1.0L*p)),t = x*y-k*p;
    t -= p;while(t < 0) t += p;
    return t;
}

inline int exgcd(int a,int b,int &x,int &y){
    if(!b){
        x = 1;y = 0;
        return a;
    }
    int g = exgcd(b,a%b,x,y);
    int t = x;x = y;y = t-(a/b)*y;
    return g;
}

inline int qpow(int a,int n,int ha){
    int res = 1;
    while(n){
        if(n & 1) res = qmul(res,a,ha);//res = 1ll*res*a%ha;
       // a = 1ll*a*a%ha;
        a = qmul(a,a,ha);
        n >>= 1;
    }
    return res;
}


inline int uqpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a;
        a = 1ll*a*a;
        n >>= 1;
    }
    return res;
}
const int MAXN = 10000+5;
bool vis[MAXN];

inline bool pdg(int x,int p){
    int t = 1;CLR(vis,0);
    FOR(i,0,p-2){
      //  DEBUG(t);
        if(vis[t]) return false;
        vis[t] = true;
        //t = 1ll*t*x%p;
        t = qmul(t,x,p);
    }
    return true;
}
int g;
inline int getg(int p){
    FOR(i,2,p-1){
        if(pdg(i,p)) return i;
    }
}

inline int calc(int p,int e,int a){
    if(e == 1){
        //DEBUG(p);
        FOR(i,0,p-1){
            //DEBUG(qpow(g,i,p));DEBUG(a%(p));
            if(qpow(g,i,p) == a%p) return i;
        }
        return -1;
    }
    int x0 = calc(p,e-1,a);
    if(x0 == -1) return -1;
   // int ha = uqpow(p,e-1)*(p-1);
    int base = uqpow(p,e-2)*(p-1);
    int ha = uqpow(p,e);
   // if(e == 2) DEBUG(base),DEBUG(ha);
   // int ha = uqpow(p,e),base = uqpow(p,e-1);
    FOR(i,0,p-1){
        int t = x0+i*base;
        if(qpow(g,t,ha) == a%ha) return t;
    }
    return -1;
}

inline void Solve(){
    int a,b,p,e;scanf("%lld%lld%lld%lld",&a,&b,&p,&e);
    g = getg(p);//DEBUG(g);
    int aa = calc(p,e,a);
    int bb = calc(p,e,b); // aa*ax = bb(mod pp)
    int pp = (p-1)*uqpow(p,e-1);int x=0,y=0;// aax-ppy = bb
    int _gcd = exgcd(aa,pp,x,y);
    if(bb%_gcd){
        puts("-1");return;
    }
    x = qmul(x,bb/_gcd,pp);
    //x = x*bb/_gcd;
    pp /= _gcd;
    x = (x%pp+pp)%pp;
  //  while(x < 0) x += pp;x %= pp;
    printf("%lld\n",x);
}

signed main(){
    //DEBUG(pdg(2,29));
 //   DEBUG(getg(29));
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}


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
const int p = 999911659;
const int phi = p-1;
const int prime[] = {0,2,3,4679,35617};

const int MAXN = 50000+5;
int n,g;

inline int qpow(int a,int n,int ha){
    int res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int fac[5][MAXN],inv[5][MAXN];

inline void prework(){
    FOR(i,1,4){
        fac[i][0] = 1;int ha = prime[i];
        FOR(j,1,ha-1) fac[i][j] = 1ll*fac[i][j-1]*j%ha;
        inv[i][ha-1] = qpow(fac[i][ha-1],ha-2,ha);
        ROF(j,ha-2,0) inv[i][j] = 1ll*inv[i][j+1]*(j+1)%ha;
    }
}

inline int C(int n,int m,int tp){
    int ha = prime[tp];
    return 1ll*fac[tp][n]*inv[tp][m]%ha*inv[tp][n-m]%ha;
}

inline int lucas(int n,int m,int tp){
    int ha = prime[tp];
    if(n < m) return 0;
    if(!m) return 1;
    if(n < ha && m < ha) return C(n,m,tp);
    return lucas(n/ha,m/ha,tp)*lucas(n%ha,m%ha,tp)%ha;
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

inline int CRT(int xx){ // 求 C(n,x) mod phi
    int aa[MAXN],x=0,y=0; // 合并x == a[i] mod (p[i])
    FOR(i,1,4) aa[i] = lucas(n,xx,i);
    int ans = aa[1],M = prime[1];
    FOR(i,2,4){
        int a = M,b = prime[i],c = (aa[i]-ans%b+b)%b;
        int g = exgcd(a,b,x,y),bg = b/g;
        x = 1ll*x*c/g % bg;
        ans += x*M;
        M *= bg;
        ans = (ans+M)%M;
    }
    return (ans+M)%M;
}

signed main(){
    prework();
    scanf("%lld%lld",&n,&g);
    if(!(g%p)){puts("0");return 0;}
    int q = std::sqrt(1.0*n),ans = 0;
    FOR(i,1,q){
        if(!(n%i)){
            (ans += CRT(i)) %= phi;
            if(n/i != i) (ans += CRT(n/i)) %= phi;
        }
    }
    printf("%lld\n",qpow(g,ans,p));
    return 0;
}

/*
 * Author: RainAir
 * Time: 2019-10-12 18:47:13
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
const int MAXN = 4e5 + 15;
const int ha = 998244353;

int n,m,k;
int a[MAXN];

int prime[MAXN],mu[MAXN],tot;
int fac[MAXN],inv[MAXN];
int p[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    if(n < 0) return 0;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(int n){
    mu[1] = 1;
    FOR(i,2,n){
        if(!p[i]) prime[++tot] = i,mu[i] = -1;
        for(int j = 1;j <= tot && i*prime[j] <= n;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])){
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = -mu[i];
        }
    }
    fac[0] = 1;
    FOR(i,1,n) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[n] = qpow(fac[n]);
    ROF(i,n-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

inline int calc(int cnt,int c,int k){ //  >= k 重复 -> <= n-k  不重复
//    return 1ll*C(cnt,k)*qpow(c,n-k)%ha;
    int ans = 0,now1 = qpow(c,n-cnt),now2 = qpow(c-1,cnt-k);
    int invc = qpow(c-1);
//    FOR(i,k,std::min(cnt,n)) (ans += 1ll*C(cnt,i)*qpow(c,n-cnt)%ha*qpow(c-1,cnt-i)%ha) %= ha,DEBUG(qpow(c-1,cnt-i));
    FOR(i,k,std::min(cnt,n)){
        if(!(cnt-i)) now2 = 1;// x^0 = 1
        (ans += 1ll*C(cnt,i)*now1%ha*now2%ha) %= ha;
        //DEBUG(now2);
        if(c != 1) now2 = 1ll*now2*invc%ha;
 //       else now2 = 1;
    }
    return ans;
}

int cnt[MAXN];

inline int TF(int x){
    int c = m/x,cnt = ::cnt[x];
//    FOR(i,1,n) if(!(a[i]%x)) ++cnt;
//    DEBUG(calc(cnt,c,0));
//    exit(0);
    return (calc(cnt,c,0)-calc(cnt,c,n-k+1)+ha)%ha;
}
int F[MAXN];

inline int koF(int x){
    int c = m/x;
    return qpow(c,n);
}

/*
int f[MAXN][MAXN];

inline int FF(int x){
//    int c = m/x,cnt = 0;
//    FOR(i,1,n) if(!(a[i]%x)) cnt++;
//    int ans = 0,now = 1;
//    FOR(i,0,n-k) (ans += 1ll*C(cnt,i)*qpow(c,n-i)%ha)%=ha,now = 1ll*now*c%ha;
    int c = m/x;CLR(f,0);
    f[0][0] = 1;
    FOR(i,0,n-1){
        FOR(j,0,n){
            if(a[i+1]%x){
                f[i+1][j] += f[i][j]*c;
            }
            else{
                f[i+1][j] += f[i][j]*(c-1);
                f[i+1][j+1] += f[i][j];
            }
        }
    }
    int ans = 0;
    FOR(i,0,n-k) ans += f[n][i];
    return ans;
}
*/
signed main(){
//    freopen("b.in","r",stdin);
//    freopen("b.out","w",stdout);
    scanf("%lld%lld%lld",&n,&m,&k);
    if(n <= 5500) prework(5500+50);
    else prework(4e5 + 5);
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n){
        int q = std::sqrt(1.0*a[i]);
        FOR(x,1,q){
            if(!(a[i]%x)){
                cnt[x]++;
                if(x*x != a[i]) cnt[a[i]/x]++;
            }
        }
    }
//    FOR(i,1,m) DEBUG(cnt[i]);
//    DEBUG(TF(3));return 0;
    if(!k && n > 5500) FOR(i,1,m) F[i] = koF(i);
    else FOR(i,1,m) F[i] = TF(i);
//    DEBUG(m);
    FOR(i,1,m){
        int ans = 0;
        FOR(j,1,m){
            if(1ll*i*j > m) break;
            int gx = 1ll*F[i*j]%ha*mu[j];
            gx = (gx+ha)%ha;
            (ans += gx)%=ha;
        }
        printf("%lld ",ans);
    }
    puts("");
    return 0;
}

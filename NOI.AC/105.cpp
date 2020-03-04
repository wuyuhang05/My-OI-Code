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

const int MAXN = 100+5;
const int MAXM = 5000+5;
const int ha = 1e9 + 7;
int n,m;
int f[MAXN][MAXN];// i 个点 桥的个数为 j 连通图个数
int g[MAXN][MAXN];// i 个点 桥的个数为 j 一般图个数
int h[MAXN]; // i 个点 连通图个数
int fac[MAXM],inv[MAXM],pw[MAXM],ninv[MAXN];

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = pw[0] = 1;
    FOR(i,1,MAXM-1) fac[i] = 1ll*fac[i-1]*i%ha,pw[i] = 2ll*pw[i-1]%ha;
    inv[MAXM-1] = qpow(fac[MAXM-1]);
    ROF(i,MAXM-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    ninv[1] = 1;
    FOR(i,2,MAXN-1) ninv[i] = 1ll*(ha-ha/i)*ninv[ha%i]%ha;
}

inline int binom(int n,int m){
    if(n < m) return 0;
    if(!m) return 1;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    prework();
    scanf("%d%d",&n,&m);
    FOR(i,1,n){
        h[i] = pw[binom(i,2)];
        FOR(j,1,i-1){
            int t = 1ll*binom(i-1,j-1)*h[j]%ha*pw[binom(i-j,2)]%ha;
            (h[i] += ha-t) %= ha;
        }
    }
    g[0][0] = 1;
    FOR(i,1,n){
        f[i][0] = h[i];
        FOR(j,1,i-1){
            FOR(a,1,i-1){
                FOR(b,0,j-1){
                    (f[i][j] += 1ll*binom(i-2,a-1)*f[a][b]%ha*f[i-a][j-b-1]%ha) %= ha;
                }
            }
            f[i][j] = 1ll*f[i][j]*binom(i,2)%ha*ninv[j]%ha;
            (f[i][0] += ha-f[i][j]) %= ha;
        }
        FOR(j,0,i-1){
            FOR(a,1,i){
                FOR(b,0,j){
                    (g[i][j] += 1ll*f[a][b]*binom(i-1,a-1)%ha*g[i-a][j-b]%ha) %= ha;
                }
            }
        }
    }
    int res = 0;
    FOR(i,0,m) (res += g[n][i]) %= ha;
    printf("%d\n",res);
    return 0;
}
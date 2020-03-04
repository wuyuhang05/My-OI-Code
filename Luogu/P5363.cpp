#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int ha = 1e9 + 9;
const int MAXN = 160000+5;
const int MAXM = 100+5;

int fac[MAXN],inv[MAXN],f[20][MAXN],g[MAXM];
int n,m;

inline int C(int up,int down){
    if(up < down || down < 0) return 0;
    return 1ll*fac[up]*inv[down]%ha*inv[up-down]%ha;
}

inline int qpow(int a,int n){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1],ha-2);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int work(int n,int m){
    int p1 = m>>1,p0 = m-p1;
    FOR(i,0,m){ // 处理某一位填 i 个 1 的方案数
        for(int j = 0;j <= i;j += 2){ // 奇数位置放 1 的数量
            (g[i] += (1ll * C(p1,j) * C(p0,i-j)%ha))%=ha;
        }
    }
    f[18][0] = 1;// 没有棋子，先手必败
    ROF(i,18,1)
        FOR(j,0,n) if(f[i][j])
            for(int k = 0;k <= m && (j+k*(1<<(i-1))) <= n;++k)
                (f[i-1][j+k*(1<<(i-1))] += 1ll*f[i][j]*g[k]%ha)%=ha;
    return f[0][n];
}

int main(){
    scanf("%d%d",&n,&m);
    if(n <= m) return puts("0"),0;
    prework();
    printf("%d\n",(C(n,m)-work(n-m,m+1)+ha)%ha);
    return 0;
}

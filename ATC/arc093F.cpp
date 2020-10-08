/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-17 09:33:50
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
const int MAXN = 16 + 1;
const int MAXM = 1e5 + 5;
const int ha = 1e9 + 7;
int f[MAXN+3][(1<<MAXN)+3];
int a[MAXN+3];
int fac[MAXM],inv[MAXM],pc[(1<<MAXN)+3];
int n,m;

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
    fac[0] = 1;
    FOR(i,1,MAXM-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXM-1] = qpow(fac[MAXM-1]);
    ROF(i,MAXM-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

signed main(){
    prework();
    scanf("%lld%lld",&n,&m);
    FOR(i,1,MAXM-1) pc[i] = pc[i>>1]+(i&1);
    FOR(i,1,m) scanf("%lld",a+i);
    std::sort(a+1,a+m+1);
    // f[i][S] 表示填到前 i 个数，S 区间最小值是这个数
    f[m+1][0] = 1;
    ROF(i,m,1){
        FOR(S,0,(1<<n)-1){
            (f[i][S] += f[i+1][S]) %= ha;
            int t = (1<<n)-S-a[i]; // 可以放的数
//            if(S == 0 && i == 1) DEBUG(t);
            FOR(j,0,n-1){
                if(S&(1<<j)) continue;
             //   if(S == 0 && i == 1) DEBUG(j),DEBUG((S|(1<<j))),DEBUG(t),DEBUG((1<<j)-1);
                (f[i][S|(1<<j)] += 1ll*f[i+1][S]*C(t,(1<<j)-1)%ha*fac[(1<<j)]%ha) %= ha;
            //    if(S == 0 && i == 1) DEBUG(f[i][S|(1<<j)]),DEBUG(f[1][1]);
            }
        }
    }
    int ans = 0;
    FOR(S,0,(1<<n)-1){
        (ans += (1ll*(pc[S]&1?ha-1:1)*f[1][S]%ha*fac[(1<<n)-S-1]%ha)) %= ha;
    }
    printf("%lld\n",1ll*ans*(1<<n)%ha);
    return 0;
}

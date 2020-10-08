/*
 * sto Qingyu orz
 * 感谢真神sqy无私的教诲。膜时队者处处阿克，只因大师sqy在他背后。不膜大师者违背了真神的旨意，真神必将降下天谴,
 * 使其天天爆零
 * 我不由自主地膜拜真神sqy。
 * Author: RainAir
 * Time: 2019-10-17 14:31:56
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

const int MAXN = 3000+5;
int ha;
int n;
int S[MAXN][MAXN],fac[MAXN],inv[MAXN],facfac[MAXN];

inline int qpow(int a,int n=ha-2,int mod=ha){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%mod;
        a = 1ll*a*a%mod;
        n >>= 1;
    }
    return res;
}

inline void prework(){
    fac[0] = 1;
    FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    S[0][0] = 1;
    FOR(i,1,MAXN-1){
//        S[i][0] = 1;
        FOR(j,1,i){
            S[i][j] = (S[i-1][j-1]+1ll*j*S[i-1][j]%ha)%ha;
        }
    }
    FOR(i,0,MAXN-1) facfac[i] = qpow(2,qpow(2,i,ha-1));
}

inline int C(int n,int m){
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    scanf("%d%d",&n,&ha);
    prework();int ans = facfac[n];
    FOR(i,1,n){
        int gx = 0,t1 = 1,b1 = qpow(2,n-i);
        FOR(j,0,i){
            //(gx += 1ll*qpow(2,qpow(2,n-i,ha-1))*qpow(qpow(2,n-i),j)%ha*S[i+1][j+1]%ha) %= ha;
            (gx += 1ll*facfac[n-i]*t1%ha*S[i+1][j+1]%ha) %= ha;
            t1 = 1ll*t1*b1%ha;
        }
        gx = 1ll*gx*C(n,i)%ha;
        if(i&1) gx = ha-gx;
        (ans += gx) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}

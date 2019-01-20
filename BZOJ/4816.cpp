#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int ha = 1000000000+7;
const int MAXN = 600000+5;

bool p[MAXN<<2];
int prime[MAXN<<2],cnt;
int mu[MAXN<<2],fr[MAXN<<2],f[MAXN<<2];

inline LL qpow(LL a,LL n){
    LL ret = 1ll;if(n < 0) n += ha-1;
    while(n){
        if(n & 1) ret = (ret*a)%ha;
        a = (a*a)%ha;
        n >>= 1;
    }
    return ret;
}

inline void pre(int limit){
    mu[1] = 1;p[1] = true;
    FOR(i,2,limit){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1;
        for(int j = 1;j <= cnt && i*prime[j] <= limit;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])) break;
            mu[i*prime[j]] = -mu[i];
        }
    }
    FOR(i,0,limit) f[i] = fr[i] = 1;
    int A = 1,B = 0;
    FOR(i,1,limit){
        B = (A+B)%ha;
        A = (B-A+ha)%ha;
        int G[3] = {qpow(B,-1),1,B};
        for(int j = i,k = 1;j <= limit;j += i,k++){
            f[j] = 1ll*f[j]*G[mu[k]+1]%ha;
            fr[j] = 1ll*fr[j]*G[1-mu[k]]%ha;
        }
    }
    FOR(i,1,limit){
        f[i] = 1ll*f[i-1]*f[i]%ha;
        fr[i] = 1ll*fr[i-1]*fr[i]%ha;
    }
}

inline void Solve(){
    int N,M;scanf("%lld%lld",&N,&M);
    if(N > M) std::swap(N,M);
    int ans = 1;
    for(int l = 1,r;l <= N;l = r+1){
        r = std::min(N/(N/l),M/(M/l));
        ans = 1ll * ans * qpow(1ll*f[r]*fr[l-1]%ha,1ll*(N/l)*(M/l))%ha;
    }
    printf("%lld\n",ans);
}

signed main(){
    int T;pre(1e6);
    scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
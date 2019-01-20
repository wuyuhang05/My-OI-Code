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

const int MAXN = 1000000+5;
bool p[MAXN<<2];
int prime[MAXN<<2],mu[MAXN<<2],cnt;
LL sum[MAXN<<2];

inline void pre(int limit){
    p[1] = true;mu[1] = 1;
    FOR(i,2,limit){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1;
        for(Re int j = 1;j <= cnt && i*prime[j] <= limit;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])) break;
            mu[i*prime[j]] = -mu[i];
        }
    }
    FOR(i,1,limit) sum[i] = sum[i-1] + mu[i];
}

inline void Solve(){
    int N,M,K;scanf("%lld%lld%lld",&N,&M,&K);
    LL ans = 0;if(N > M) std::swap(N,M);
    for(int l = 1,r;l <= N;l = r+1){
        r = std::min(N/(N/l),M/(M/l));
        ans += (N/(l*K))*(M/(l*K))*(sum[r]-sum[l-1]);
    }
    printf("%lld\n",ans);
}

signed main(){
    pre(MAXN-5);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
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

const int MAXN = 10000000+5;
int prime[MAXN],mu[MAXN],g[MAXN],cnt;
bool p[MAXN];
LL sum[MAXN];

inline void pre(int limit){
    mu[1] = 1;
    FOR(i,2,limit){
        if(!p[i]){
            mu[i] = -1;prime[++cnt] = i;
        }
        for(Re int j = 1;j <= cnt && i*prime[j] <= limit;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])) break;
            mu[prime[j]*i] = -mu[i];
        }
    }
    FOR(j,1,cnt) for(int i = 1;i * prime[j] <= limit;++i) g[i*prime[j]] += mu[i];
    FOR(i,1,limit) sum[i] = sum[i-1] + 1ll*g[i];
}

inline void Solve(){
    int N,M;scanf("%d%d",&N,&M);
    LL ans = 0ll;if(N > M) std::swap(N,M);
    for(int l = 1,r;l <= N;l = r+1){
        r = std::min(N/(N/l),M/(M/l));
        ans += 1ll*(N/l)*(M/l)*(sum[r]-sum[l-1]);
        //DEBUG(sum[r]);DEBUG(sum[l-1]);
    }
    printf("%lld\n",ans);
}

int main(){
    int T;scanf("%d",&T);pre(MAXN-2);
    while(T--) Solve();
    return 0;
}
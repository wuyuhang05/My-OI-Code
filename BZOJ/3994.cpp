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

const int MAXN = 5000000+5;

bool p[MAXN];
int prime[MAXN],cnt;
int mu[MAXN],d[MAXN],ys[MAXN];
int sumu[MAXN],sumd[MAXN];

inline void pre(int limit){
    p[1] = true;mu[1] = ys[1] = 1;
    FOR(i,2,limit){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1,d[i] = 1,ys[i] = 2;
        for(Re int j = 1;j <= cnt && i * prime[j] <= limit;++j){
            p[i*prime[j]] = true;
            if(!(i%prime[j])){
                mu[i*prime[j]] = 0;
                ys[i*prime[j]] = ys[i]/(d[i]+1)*(d[i]+2);
                d[i*prime[j]] = d[i]+1;
                break;
            }
            mu[i*prime[j]] = -mu[i];ys[i*prime[j]] = ys[i]<<1;
            d[i*prime[j]] = 1;
        }
    }
    FOR(i,1,limit) sumu[i] = sumu[i-1]+mu[i];
    FOR(i,1,limit) sumd[i] = sumd[i-1]+ys[i];
}

inline void Solve(){
    int N,M;scanf("%d%d",&N,&M);
    if(N > M) std::swap(N,M);
    LL ans = 0;
    for(int l = 1,r;l <= N;l = r+1){
        r = std::min(N/(N/l),M/(M/l));
        ans += 1ll*(sumu[r]-sumu[l-1])*sumd[N/l]*sumd[M/l];
    }
    printf("%lld\n",ans);
}

int main(){
    pre(MAXN-5);
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
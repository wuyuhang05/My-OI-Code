#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
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
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
int N,K;
int ans=LLONG_MAX;

signed main(){
    scanf("%lld%lld",&N,&K);
    int M = K;
    int q = std::sqrt(K);
    FOR(i,2,q){
        if(K%i) continue;
        int cnt = 0,tot = 0;
        while(!(K%i)) K /= i,tot++;
        int tt=N;
        while(tt) cnt += tt/i,tt /= i;
        ans = std::min(ans,cnt/tot);
    }
    if(K > 1){
        int cnt = 0,tt = N;
        while(tt) cnt += tt/K,tt /= K;
        ans = std::min(ans,cnt);
    }
    printf("%lld\n",ans);
    return 0;
}

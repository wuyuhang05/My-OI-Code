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
const int MAXN = 1000 + 5;
const int MAXK = 100000+5;
int N,M,K,P;
int a[MAXN][MAXN];
int h[MAXN],l[MAXN];
int f[MAXK],g[MAXK];
std::priority_queue<int> q1,q2;

signed main(){
    scanf("%lld%lld%lld%lld",&N,&M,&K,&P);
    FOR(i,1,N){
        int sum = 0;
        FOR(j,1,M){
            int x;scanf("%lld",&x);
            h[i] += x;l[j] += x;
        }
    }
    FOR(i,1,N) q1.push(h[i]);
    FOR(i,1,M) q2.push(l[i]);
    FOR(i,1,K){
        LL x = q1.top();q1.pop();
        LL y = q2.top();q2.pop();
        f[i] = f[i-1] + x;g[i] = g[i-1] + y;
        q1.push(x-P*M);q2.push(y-P*N);
    }
    LL ans = f[0] + g[K];
    FOR(i,1,K) ans = std::max(ans,f[i]+g[K-i]-i*(K-i)*P);
    printf("%lld\n",ans);
    return 0;
}

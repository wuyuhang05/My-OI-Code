/*
 * Author: RainAir
 * Time: 2019-08-09 18:48:30
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e6 + 5;
const int MAXM = 20 + 5;

U int a[MAXM],b[MAXM],c[MAXM];
int n,m,N;
int h[MAXN],cnt[MAXN];
LL f[MAXN],g[MAXN],dp[MAXN];

inline U int calc(int i,U int e){
    U int res = a[i]*e*e+b[i]*e+c[i];
    return res;
}

inline void fmt1(LL *a){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += mid<<1){
            for(int j = 0;j < mid;++j){
                a[i+j] += a[i+mid+j];
            }
        }
    }
}

inline void fmt2(LL *a){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += mid<<1){
            for(int j = 0;j < mid;++j){
                a[i+mid+j] += a[i+j];
            }
        }
    }
}


signed main(){
    scanf("%d%d",&n,&m);N = 1<<m;
    FOR(i,1,m){
        scanf("%u%u%u",a+i,b+i,c+i);int t;scanf("%d",&t);
        FOR(j,1,t){
            int x;scanf("%d",&x);h[x] |= (1<<(i-1));
        }
    }
    FOR(i,1,n) g[h[i]]++;
    fmt1(g);
    FOR(i,0,N-1){
        cnt[i] = cnt[i>>1]+(i&1);
        f[i] = g[i]*(g[i]-1)/2;
        if(!(cnt[i]&1)) f[i] = -f[i];
    }
    fmt2(f);
    FOR(S,1,N-1){
        FOR(i,1,m){
            if((1<<(i-1))&S){
                LL gx = calc(i,f[S]-f[S^(1<<(i-1))]);
                dp[S] = std::max(dp[S],dp[S^(1<<(i-1))]+gx);
            }
        }
    }
    printf("%lld\n",dp[N-1]);
    return 0;
}

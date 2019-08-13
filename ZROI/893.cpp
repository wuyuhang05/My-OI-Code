/*
 * Author: RainAir
 * Time: 2019-08-10 18:17:07
 */
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
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
#define int LL
const int MAXN = 3e6 + 5;
int n,rev[MAXN],N;
int ans[MAXN],res;
U LL a[MAXN];
char str[MAXN];

inline int dfs1(int step,U LL bit){
    if(!bit) return 0;
    if(!step) return bit;
    int x = 1ll<<step-1;
    U LL lbit = bit >> x,rbit = bit&((1ll<<x)-1);
    return dfs1(step-1,lbit&rbit)+dfs1(step-1,lbit|rbit)+dfs1(step-1,lbit^rbit);
}

inline int calc(int step,U LL bit){
    if(step == 4){
        res += ans[bit];return 19260817;
    }
    if(!step){
        res += bit;return 19260817;
    }
    int x = 1ll<<step-1;
    U LL L = bit>>x,R = bit&((1ll<<x)-1);
    return ((L&R)?calc(step-1,L&R):0)+((L|R)?calc(step-1,L|R):0)+((L^R)?calc(step-1,L^R):0);
}

// 6 bits
inline void dfs2(int step,U LL *a){
    if(step <= 0){
        calc(step+6,a[0]);return;
    }
    int x = 1ll<<step-1;
    U LL A[x+2],O[x+2],X[x+2];
    bool fg1=false,fg2=false,fg3=false;
    FOR(i,0,x-1){
        A[i] = a[i]&a[i+x];
        O[i] = a[i]|a[i+x];
        X[i] = a[i]^a[i+x];
        if(A[i]) fg1 = true;
        if(O[i]) fg2 = true;
        if(X[i]) fg3 = true;
    }
    if(fg1) dfs2(step-1,A);
    if(fg2) dfs2(step-1,O);
    if(fg3) dfs2(step-1,X);
}

signed main(){
    scanf("%lld",&n);scanf("%s",str);N = 1<<n;
    FOR(i,0,(1ll<<(1ll<<4))-1) ans[i] = dfs1(4,i);
    FOR(i,1,N-1) rev[i] = rev[i>>1]>>1|((i&1)<<n-1);
    FOR(i,0,N-1){
        if(i < rev[i]) std::swap(str[i],str[rev[i]]);
    }
    FOR(i,0,N-1){
        int x = str[i]-'0';
        a[i>>6] |= (x<<(i&63));
    }
    dfs2(n-6,a);
    printf("%lld\n",res);
    return 0;
}

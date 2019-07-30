/*
 * Author: RainAir
 * Time: 2019-07-27 17:41:36
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
#define int LL
const int MAXN = 2e5 + 5;
int n,a[MAXN],b[MAXN];

inline int calc(int x){
    int res = 0;
    while(x) res++,x /= 2;
    return res;
}

int t[MAXN];

inline void merge(int *p,int mod){
    int i=1,j;
    for(j = 1;j <= n;++j){
        if(p[j] >= mod) break;
    }
    FOR(k,1,n) t[k] = p[k]%mod;
    int k = 0,tt = j;
    while(i < tt && j <= n){
        if(t[i] < t[j]) p[++k] = t[i++];
        else p[++k] = t[j++];
    }
    while(i < tt) p[++k] = t[i++];
    while(j <= n) p[++k] = t[j++];
 //   assert(k == n);
}

inline int sqyak(int mod){
    int r = n,ans = 0;
    FOR(l,1,n){
        while(a[l]+b[r] >= mod && r > 0) r--;
        ans += n-r;
    }
    return ans;
}

inline bool chk(int mod){
    merge(a,mod<<1);merge(b,mod<<1);
    int ans = sqyak(mod)+sqyak(3*mod)-sqyak(mod<<1);
    return ans&1;
}

inline void Solve(int ttt){
    scanf("%lld",&n);int lg = 0;
    FOR(i,1,n) scanf("%lld",a+i);
    FOR(i,1,n) scanf("%lld",b+i);
    FOR(i,1,n) lg = std::max(lg,calc(a[i]+b[i]));
    lg = 62;
    std::sort(a+1,a+n+1);std::sort(b+1,b+n+1);
    int ans = 0;
    ROF(i,lg,0){
        int mod = 1ll<<i;
        if(chk(mod)) ans += mod;
    }
    printf("Case #%lld: %lld\n",ttt,ans);
}

signed main(){
    int T;scanf("%lld",&T);
    FOR(i,1,T) Solve(i);
    return 0;
}

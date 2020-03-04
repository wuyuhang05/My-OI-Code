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
#define int LL
int id[23333],di[23333],tot;

inline int gcd(int a,int b){
    return !b ? a : gcd(b,a%b);
}

inline int lcm(int a,int b){
    if(!a) return b;if(!b) return a;
    return 1ll*a*b/gcd(a,b);
}
int lim[2333];
int f[20][48+3][2520+3];

inline int dp(int i,int j,int k,int l){
    if(!i) return !(k%di[j]);
    if(!l && f[i][j][k] != -1) return f[i][j][k];
    int &res = f[i][j][k];res = 0;
    int up = l ? lim[i] : 9;
    FOR(x,0,up){
        int nxt = j==0 ? id[x] : id[lcm(di[j],x)];
        res += dp(i-1,nxt,(k*10+x)%2520,l&&(x==up));
    }
    return res;
}

inline int calc(int x){
    if(!x) return 0;int len = 0;
    while(x) lim[++len] = x%10,x /= 10;
    // FOR(i,1,len) DEBUG(lim[i]);
    int ans = 0;
    return dp(len,0,0,1);
}

inline void Solve(){
    int l,r;scanf("%lld%lld",&l,&r);
    printf("%lld\n",calc(r)-calc(l-1));
}

signed main(){
    CLR(f,-1);DEBUG(1);
    tot = 0;id[tot = 1] = 1;di[tot] = 1;
    FOR(S,1,(1<<10)-1){
        int t = 1;
        FOR(i,0,9){
            if((S>>i)&1) t = lcm(t,i+1);
        }
        if(!id[t]) id[t] = ++tot,di[tot] = t;
    }
    // FOR(i,1,tot) DEBUG(di[i]);
    // DEBUG(tot);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
/*
f[i][j][k][0/1]
f[i][j][k] -> f[i+1][lcm(j,x)][(k*10+x)%lcm][0/1]
前 i 个 数字的 lcm 是 j，当前数字%lcm 是 k 是否卡上界
*/
/*
 * Author: RainAir
 * Time: 2019-10-08 10:56:26
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
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 19;
const int MAXM = (1<<10)+3;

int f[MAXN][MAXN][MAXM],cs;
int nxt[MAXM][MAXN],pc[MAXM];
// 前 i 位， 子序列长度为 j， dp 状态为 S

inline int prepare(int S,int num){// S add i
    FOR(i,num,9){
        if(S&(1<<i)){
            return (S^(1<<i))|(1<<num);
        }
    }
    return S|(1<<num);
}

int a[MAXN],len,K;

inline int dfs(int i,int S,int lim,int zero){
    if(!i) return pc[S] == K;
    if(!lim && f[K][i][S] != -1) return f[K][i][S];
    int up = lim ? a[i] : 9;int ans = 0;
    FOR(x,0,up){
        ans += dfs(i-1,(zero && !x) ? S : nxt[S][x],lim&&x==up,zero&&!x);
    }
    if(!lim) f[K][i][S] = ans;
    return ans;
}

inline int calc(int x){
    len = 0;
    while(x) a[++len] = x%10,x /= 10;
    return dfs(len,0,1,1);
}

inline void Solve(){
    int L,R;scanf("%lld%lld%lld",&L,&R,&K);
//    DEBUG(calc(R));DEBUG(calc(L-1));
    printf("Case #%lld: %lld\n",++cs,calc(R)-calc(L-1));
}

signed main(){
    CLR(f,-1);
    FOR(i,1,(1<<10)) pc[i] = pc[i>>1]+(i&1);
    FOR(S,0,(1<<10)-1) FOR(i,0,9) nxt[S][i] = prepare(S,i);
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}

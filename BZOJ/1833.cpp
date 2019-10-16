/*
 * Author: RainAir
 * Time: 2019-10-07 19:45:30
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
const int MAXN = 12+2;
int f[MAXN][2][2],pw[MAXN];
int a[MAXN],len;
int ans[MAXN],suf[MAXN];

inline int dfs(int now,int i,int fg,int zero){
    if(i == len+1) return 0;
    if(f[i][fg][zero] != -1) return f[i][fg][zero];
    int ans = 0;
    if(fg){
        FOR(x,0,a[i]-1){
            if(zero && !x) ans += dfs(now,i+1,0,1);
            else{
                ans += dfs(now,i+1,0,0);
                if(now == x) ans += pw[len-i];
            }
        }
        if(zero && !a[i]) ans += dfs(now,i+1,1,1);
        else{
            ans += dfs(now,i+1,1,0);
            if(now == a[i]) ans += suf[i];
        }
    }
    else{
        FOR(x,0,9){
            if(zero && !x) ans += dfs(now,i+1,0,1);
            else{
                ans += dfs(now,i+1,0,0);
                if(now == x) ans += pw[len-i];
            }
        }
    }
    return f[i][fg][zero] = ans;
}

inline void calc(int x,int d){
    len = 0;
    while(x) a[++len] = x%10,x /= 10;
    std::reverse(a+1,a+len+1);
    suf[len] = 1;
    ROF(i,len-1,0) suf[i] = suf[i+1] + a[i+1]*pw[len-i-1];
    FOR(i,0,9){
        CLR(f,-1);
        ans[i] += d*dfs(i,1,1,1);
    }
}

signed main(){
    int l,r;scanf("%lld%lld",&l,&r);
    pw[0] = 1;
    FOR(i,1,MAXN-1) pw[i] = pw[i-1]*10;
    calc(l-1,-1);
    calc(r,1);
    FOR(i,0,9) printf("%lld ",ans[i]);puts("");
    return 0;
}


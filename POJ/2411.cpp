/*
 * Author: RainAir
 * Time: 2019-08-25 11:31:00
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
const int MAXN = (1<<15) + 5;
int f[2][MAXN],now;
int n,m;

inline void Solve(){
    if(n < m) std::swap(n,m);
    now = 0;CLR(f,0);
    f[now][(1<<m)-1] = 1;
    FOR(i,0,n-1){
        FOR(j,0,m-1){
            CLR(f[now^1],0);
            FOR(S,0,(1<<m)-1){
                if(!(S&(1<<j))){
                    f[now^1][S|(1<<j)] += f[now][S];
                }
                else{
                    f[now^1][S^(1<<j)] += f[now][S];
                    if(j > 0 && !(S&(1<<j-1))){
                        f[now^1][S|(1<<j-1)] += f[now][S];
                    }
                }
            }
            now ^= 1;
        }
    }
    printf("%lld\n",f[now][(1<<m)-1]);
}

signed main(){
    while(~scanf("%lld%lld",&n,&m) && (n+m)) Solve();
    return 0;
}

/*
 * Time: 2019-11-14 17:04:42
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

const int MAXN = 1e5 + 5;
const int MAXM = 34;
#define int LL
int n,k;
int f[MAXN][MAXM+1],g[MAXN][MAXM+1],t[MAXN][MAXM+1];
int to[MAXN],val[MAXN];

signed main(){
    scanf("%lld%lld",&n,&k);
    FOR(i,1,n) scanf("%lld",to+i),++to[i];
    FOR(i,1,n) scanf("%lld",val+i);
    FOR(i,1,n) f[i][0] = val[i],g[i][0] = val[i],t[i][0] = to[i];
    FOR(i,1,MAXM){
        FOR(j,1,n){
            t[j][i] = t[t[j][i-1]][i-1];
            f[j][i] = f[j][i-1]+f[t[j][i-1]][i-1];
            g[j][i] = std::min(g[j][i-1],g[t[j][i-1]][i-1]);
        }
    }
    FOR(i,1,n){
        int ans1 = 0,ans2 = 1e18,now = i;
        FOR(j,0,MAXM){
            if((k>>j)&1) ans1 += f[now][j],ans2 = std::min(ans2,g[now][j]),now = t[now][j];
        }
        printf("%lld %lld\n",ans1,ans2);
    }
    return 0;
}

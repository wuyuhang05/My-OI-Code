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
int f[MAXN][2];
int n,a[MAXN];

inline LL dfs(int x,bool flag){
    if(x < 0 || x > n) return 0;
    if(f[x][flag] != LLONG_MIN) return f[x][flag];
    f[x][flag] = -1;
    int sgn = flag ? 1 : -1;
    LL res = dfs(x+sgn*a[x],flag^1);
    if(res != -1) f[x][flag] = res+a[x];
    return f[x][flag];
}

signed main(){
    scanf("%lld",&n);
    FOR(i,2,n) scanf("%lld",a+i);
    FOR(i,1,n) f[i][0] = f[i][1] = LLONG_MIN;
    FOR(i,1,n) FOR(j,0,1) dfs(i,j);
    FOR(i,2,n){
        if(f[i][0] == -1){
            printf("%lld\n",f[i][0]);
        }
        else printf("%lld\n",f[i][0]+i-1);
    }
    return 0;
}

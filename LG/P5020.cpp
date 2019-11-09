/*
 * Author: RainAir
 * Time: 2019-11-07 20:33:28
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

const int MAXN = 100+5;
const int MAXM = 25000+5;
int n,a[MAXN],f[MAXM];

inline void Solve(){
    scanf("%d",&n);int m = 0;
    FOR(i,1,n) scanf("%d",a+i),m = std::max(m,a[i]);
    std::sort(a+1,a+n+1);
    int ans = 0;
    FOR(i,1,n){
        if(!f[a[i]]) ans++;
        f[a[i]] = 1;
        FOR(j,a[i],m){
            f[j] |= f[j-a[i]];
        }
    }
    printf("%d\n",ans);
    CLR(f,0);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

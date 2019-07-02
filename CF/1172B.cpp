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

const int MAXN = 2e5 + 5;
const int ha = 998244353;
int n;
LL fac[MAXN],du[MAXN];

int main(){
    scanf("%d",&n);
    FOR(i,1,n-1){
        int x,y;scanf("%d%d",&x,&y);du[x]++;du[y]++;
    }
    LL ans = 1;fac[0] = 1;
    FOR(i,1,n) fac[i] = 1ll*fac[i-1]*i%ha;
    FOR(i,1,n) ans = 1ll*ans*fac[du[i]]%ha;
    printf("%lld\n",ans*n%ha);
    return 0;
}

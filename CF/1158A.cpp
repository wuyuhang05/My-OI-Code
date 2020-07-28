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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
int n,m,a[MAXN],b[MAXN];

int main(){
    scanf("%d%d",&n,&m);int mn=1e9,mx=-1e9;
    FOR(i,1,n) scanf("%d",a+i),mx = std::max(mx,a[i]);
    FOR(i,1,m) scanf("%d",b+i),mn = std::min(mn,b[i]);
    if(mx > mn){
        puts("-1");return 0;
    }
    LL ans = 0;
    FOR(i,1,n) ans += 1ll*m*a[i];
    FOR(i,1,m) ans += b[i];
    std::sort(a+1,a+n+1);
    bool flag = 0;
    FOR(i,1,m) if(b[i] == a[n]) flag = 1;
    if(!flag) ans -= 1ll*a[n]*(m-1)+a[n-1];
    else ans -= 1ll*a[n]*m;
    printf("%lld\n",ans);
    return 0;
}

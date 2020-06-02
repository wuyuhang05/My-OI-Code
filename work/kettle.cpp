#include<bits/stdc++.h>

#define fi first
#define se second
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
#define int LL
const int MAXN = 1e6 + 5;
int a[MAXN],n,k;

signed main(){
    freopen("kettle.in","r",stdin);
    freopen("kettle.out","w",stdout);
    scanf("%lld%lld",&n,&k);++k;
    FOR(i,1,n) scanf("%lld",a+i),a[i] += a[i-1];
    int ans = 0;
    FOR(i,k,n){
        ans = std::max(ans,a[i]-a[i-k]);
    }
    printf("%lld\n",ans);
    return 0;
}

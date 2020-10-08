#include <bits/stdc++.h>

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

const int MAXN = 200+5;
const int MAXM = 30 +5;
int n,k;
LL f[MAXN][MAXM];
LL a[MAXN];
LL suf[MAXN];

int main(){
    //freopen("C.in","r",stdin);
    //freopen("C.out","w",stdout);
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%lld",a+i);a[0] = -1e18;
    ROF(i,n,1) suf[i] = suf[i+1]+a[i];
    CLR(f,0x3f);
    f[0][0] = 0;
    FOR(i,1,n){
        FOR(j,1,std::min(i,k)){
            FOR(k,0,i-1){
                LL gx = 0;
                FOR(l,k+1,i-1){
                    gx += std::min(a[l]-a[k],a[i]-a[l]);
                }
                f[i][j] = std::min(f[i][j],f[k][j-1]+gx);
            }
        }
    }
    LL ans = 1e18;
    FOR(i,1,n){
        ans = std::min(ans,f[i][k]+suf[i+1]-(n-i)*a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}
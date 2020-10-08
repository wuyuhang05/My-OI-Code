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

const int MAXN = 1e5 + 5;
int n,k;LL a[MAXN];
int f[MAXN];

inline int get(int l,int r){
    if(l+1 >= r) return 0;
    LL mid = (a[l] + a[r]) >> 1;
    int p = std::lower_bound(a+l,a+r+1,mid)-a;
    LL ans = 0;
    FOR(i,p-1,p+1) if(i >= l && i <= r) ans = std::max(ans,std::min(a[i]-a[l],a[r]-a[i]));
    return ans;
}

inline bool chk(LL k){
    f[0] = 0;f[1] = 1;
    int p = 1;
    FOR(i,2,n){
        if(a[i]-a[1] <= k) f[i] = 1;
        else f[i] = 1e9;
        while(p <= i && get(p,i) > k) ++p;
        f[i] = std::min(f[i],f[p]+1);
    }
    int ans = 1e9;
    ROF(i,n,1){
        if(a[n]-a[i] <= k) ans = std::min(ans,f[i]);
    }
    return ans <= ::k;
}

int main(){
    //freopen("A.in","r",stdin);
    //freopen("A.out","w",stdout);
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%lld",a+i);
    LL l = 0,r = 2e9,ans = -1;
    while(l <= r){
        LL mid = (l+r)>>1;
        if(chk(mid)) ans = mid,r = mid-1;
        else l = mid+1;
    }
    printf("%lld\n",ans);
    return 0;
}

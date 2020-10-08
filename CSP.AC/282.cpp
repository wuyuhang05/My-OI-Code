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

const int MAXN = 5e5 + 5;

int a[MAXN],n;
P b[MAXN];
bool vis[MAXN];

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i),b[i] = MP(a[i],i);
    std::sort(b+1,b+n+1);
    FOR(i,1,n/2) vis[b[i].se] = 1;
    int tp = 0;FOR(i,n/2+1,n) tp += vis[i];
    LL ans = 0;
    std::vector<int> p1,p2;
    FOR(i,1,n/2) if(!vis[i]) p1.pb(i);
    FOR(i,n/2+1,n) if(vis[i]) p2.pb(i);
    FOR(i,0,tp-1) ans += p2[i]-p1[tp-i-1];
    printf("%lld\n",ans);
    return 0;
}
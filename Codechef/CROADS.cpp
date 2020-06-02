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

inline void Solve(){
    int n;scanf("%d",&n);LL ans = 0;
    if(__builtin_popcount(n) == 1) {puts("-1");return;}
    FOR(i,0,30){
        ans += 1ll*(1ll<<i)*((n>>i)-(n>>(i+1)));
    }
    printf("%lld\n",ans-1);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

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

std::map<LL,LL> S;
LL n,a,b,c,d;

inline LL dp(LL n){
    if(S.count(n)) return S[n];
    LL res = 1e18;
    if(n <= res/d) res = n*d;
    LL t = n/2;
    res = std::min(res,dp(t)+a+std::abs(n-2*t)*d);
    t = (n+1)/2;
    res = std::min(res,dp(t)+a+std::abs(n-2*t)*d);
    t = n/3;
    res = std::min(res,dp(t)+b+std::abs(n-3*t)*d);
    t = (n+2)/3;
    res = std::min(res,dp(t)+b+std::abs(n-3*t)*d);
    t = n/5;
    res = std::min(res,dp(t)+c+std::abs(n-5*t)*d);
    t = (n+4)/5;
    res = std::min(res,dp(t)+c+std::abs(n-5*t)*d);
    return S[n] = res;
}

inline void Solve(){
    S.clear();scanf("%lld%lld%lld%lld%lld",&n,&a,&b,&c,&d);
    S[0] = 0;S[1] = d;
    printf("%lld\n",dp(n));
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

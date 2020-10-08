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
int n;
LL a[MAXN];

inline bool chk(LL k){
    FOR(i,2,n){
        if(a[i-1]+k*(i-1) < a[i]+k*i) return 0;
    }
    return 1;
}

int main(){
    scanf("%d",&n);FOR(i,1,n) scanf("%lld",a+i);
    LL l = 0,r = 2e9,ans = -1;
    while(l <= r){
        LL mid = (l + r) >> 1;
        if(chk(mid)) ans = mid,l = mid+1;
        else r = mid-1;
    }
    printf("%lld\n",ans);
    return 0;
}
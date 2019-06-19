#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 5000000+5;
bool p[MAXN];
int mu[MAXN],phi[MAXN],prime[MAXN],cnt;
LL sum1[MAXN];int sum2[MAXN];

inline void pre(int n=MAXN-5){
    phi[1] = mu[1] = 1;
    FOR(i,2,n){
        if(!p[i]){
            prime[++cnt] = i;
            mu[i] = -1;phi[i] = i-1;
        }
        for(Re int j = 1;j <= cnt && i*prime[j] <= n;++j){
            p[i*prime[j]] = true;
            if(i%prime[j]){
                phi[i*prime[j]] = phi[i]*phi[prime[j]];
                mu[i*prime[j]] = -mu[i];
            }
            else{
                phi[i*prime[j]] = phi[i]*prime[j];
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    FOR(i,1,n) sum1[i] = sum1[i-1]+phi[i],sum2[i] = sum2[i-1]+mu[i];
}

std::unordered_map<LL,LL> S1;
std::unordered_map<int,int> S2;

inline LL calc1(LL x){
    if(x <= MAXN-5) return sum1[x];
    if(S1[x]) return S1[x];
    LL ans = x*(x+1)/2;
    for(Re LL l=2,r;l <= x && r<2147483647;l = r+1){
        r = x/(x/l);
        ans -= calc1(x/l)*(r-l+1);
    }
    return S1[x] = ans;
}

inline int calc2(int x){
    if(x <= MAXN-5) return sum2[x];
    if(S2[x]) return S2[x];
    int ans = 1;
    for(Re int l = 2,r;l >= 0 && l <= x && r<2147483647;l = r+1){
        r = x/(x/l);
        ans -= calc2(x/l)*(r-l+1);
    }
    return S2[x] = ans;
}

inline void Solve(){
    int n;scanf("%d",&n);
    printf("%lld %d\n",calc1(n),calc2(n));
}

int main(){
    pre();
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

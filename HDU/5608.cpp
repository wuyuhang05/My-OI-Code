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

const int MAXN = 2000000+5;
const int ha = 1e9 + 7;
bool p[MAXN];
int prime[MAXN],mu[MAXN],cnt;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

inline void pre(int n=MAXN-5){
    mu[1] = 1;p[1] = 1;
    FOR(i,2,n){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1;
        for(int j = 1;j <= cnt && i*prime[j] <= n;++j){
            p[i*prime[j]] = true;
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];
            else{
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    FOR(i,1,n) mu[i] = (mu[i-1]+mu[i]+ha)%ha;
}

std::unordered_map<int,int> S;

inline int calc(int x){
    if(x <= MAXN-10) return mu[x];
    if(S[x]) return S[x];
    int ans = 1;
    for(int l = 2,r;l > 0 && l <= x;l = r+1){
        r = x/(x/l);
        ans = (ans-1ll*calc(x/l)*(r-l+1)%ha+ha)%ha;
    }
    return S[x] = ans;
}

int inv6 = qpow(6),inv2 = qpow(2);

inline int get(LL x){
    int res = 1ll*x*(x+1)%ha*(2*x+1)%ha;
    res = 1ll*res*inv6%ha;
    res = (1ll*res+2ll*x)%ha;
    int t = 3ll*x%ha*(x+1)%ha*inv2%ha;
    res = (res-t+ha)%ha;
    return res;
}

inline int get(int l,int r){
    return (get(r)-get(l-1)+ha)%ha;
}

inline void Solve(){
    int ans = 0,x;scanf("%d",&x);
    for(int l = 1,r;l <= x;l = r+1){
        r = x/(x/l);
        int t = 1ll*calc(x/l)*get(l,r)%ha;
       // DEBUG(l);DEBUG(r);DEBUG(t);
        ans = ((ans+t)%ha+ha)%ha;
    }
    printf("%d\n",ans);
}

int main(){
    pre();
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

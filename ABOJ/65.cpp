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

const int MAXN = 200000+5;
const int MAXM = 10000000+5;
const int ha = 998244353;
bool p[MAXN+100];
int prime[MAXN+100],mu[MAXN+100],cnt;
LL a[MAXM+100],b[MAXM+100];

inline void pre(){
    p[1] = mu[1] = 1;
    FOR(i,2,MAXN-2){
        if(!p[i]) prime[++cnt] = i,mu[i] = -1;
        for(int j = 1;j <= cnt && i*prime[j] <= MAXN-2;++j){
            p[i*prime[j]] = true;
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];
            else{
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    a[1] = 1;
    FOR(i,2,MAXM-2) a[i] = (i&1) ? (((i>>1)&1) ? -a[(i>>1)+1] : a[(i>>1)+1]) : -a[i>>1];
    FOR(i,1,MAXM-2) b[i] = b[i-1] + a[i];
}

inline int calca(LL x){
    return x <= MAXM-2 ? a[x] : ((x&1) ? (((x>>1)&1) ? -calca((x>>1)+1) : calca((x>>1)+1)) : -calca(x>>1));
}

inline int calcb(LL x){
    return x <= MAXM-2 ? b[x] : ((x&1) ? (calcb(x>>2)<<1)+calca(x) : (calcb(x>>2)<<1));
}

int n;
LL f[MAXN],g[MAXN];

int main(){
    scanf("%d",&n);pre();
    FOR(i,1,n) scanf("%lld",f+i),f[i] = calcb(f[i])%ha;
    FOR(i,1,n){
        for(int j = i;j <= n;j += i){
            g[j] += mu[j/i]*f[i];
            if(g[j] >= ha) g[j] -= ha;
            if(g[j] < 0) g[j] += ha;
        }
    }
    int ans = 1;
    FOR(i,1,n) ans = 1ll*ans*g[i]%ha;
    printf("%d\n",ans);
    return 0;
}

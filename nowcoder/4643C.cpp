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

const int MAXN = 3e5 + 5;
const int ha = 998244353;
int n,p,q;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}
int f[MAXN],g[MAXN];

int main(){
    scanf("%d%d%d",&n,&p,&q);
    int st;
    if(p){
        g[3] = f[3] = 1;st = 4;
    }
    else st = 5;
    FOR(i,st,n){
        int gx = (2ll*p%ha*g[i-2]%ha+2ll*q%ha*g[i-3]%ha)%ha;
        int t = (1ll*(i-2)*p%ha+1ll*(i-4)*q%ha)%ha;
        t = qpow(t);
        f[i] = (1+1ll*gx*t%ha)%ha;
        g[i] = (g[i-1]+f[i])%ha;
    }
    printf("%lld\n",(LL)(f[n-1]+1));
    return 0;
}

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

const int MAXN = 1e5 + 5;
const LL ha = 1234567891;

LL k,a,n,d;
int fac[MAXN];

inline LL qpow(LL a,int n=ha-2){
	LL res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline LL cha(LL y[],int k,LL n){// 取值[0..k]
    LL ans = 0;
    FOR(i,0,k){
        LL up = y[i]%ha,down = 1;
        FOR(j,0,k){
            if(i == j) continue;
            up = 1ll*up*((n%ha-j+ha)%ha)%ha;
            down = 1ll*down*((i-j+ha)%ha)%ha;
        }
        (ans += 1ll*up*qpow(down)%ha) %= ha;
    }
    return ans;
}

LL f[MAXN],g[MAXN];

inline void Solve(){
    CLR(f,0);CLR(g,0);
    scanf("%lld%lld%lld%lld",&k,&a,&n,&d);
    FOR(i,1,k+4) f[i] = (f[i-1]+qpow(i,k)) %ha;
    FOR(i,1,k+4) (f[i] += f[i-1]) %= ha;
    g[0] = cha(f,k+4,a);
    FOR(i,1,k+4) g[i] = (g[i-1]+cha(f,k+4,a+1ll*i*d));
//    DEBUG(g[k+4]);
    printf("%lld\n",cha(g,k+4,n));
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

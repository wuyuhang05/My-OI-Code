#include<bits/stdc++.h>

#define fi first
#define se second
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int ha = 1e9 + 7;
const int MAXN = 1e5 + 5;

int fac[MAXN],inv[MAXN],n,m,k,U[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

int y[MAXN];
inline int cha(int n,int m){// [1..n]^m
    int up = 1,ans = 0;
    FOR(i,1,m+1) y[i] = (y[i-1]+qpow(i,m))%ha;
    if(n <= m+1) return y[n];
    FOR(i,0,m+1) up = 1ll*up*(n-i+ha)%ha;
    FOR(i,0,m+1){
        int t = 1ll*up*qpow((n-i+ha)%ha)%ha;
        t = 1ll*t*inv[i]%ha*inv[m+1-i]%ha;
        if((m+1-i)&1) t = (ha-t);
        (ans += 1ll*t*y[i]%ha) %= ha;
    }
    return ans;
}

inline int C(int n,int m){
    if(n < m) return 0;
    if(m < 0) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int h[MAXN],r[MAXN],g[MAXN];

int main(){
    prework();
    scanf("%d%d%d",&n,&m,&k);
    FOR(i,1,m) scanf("%d",U+i);
    FOR(i,1,m) scanf("%d",r+i);
    FOR(i,1,m){
//        int chk = 0;
//        FOR(j,1,U[i]){
//            (chk += 1ll*qpow(j,n-r[i])*qpow(U[i]-j,r[i]-1)%ha) %= ha;
//        }
        FOR(k,0,r[i]-1){
            int t = 1ll*C(r[i]-1,k)*qpow(U[i],k)%ha*cha(U[i],n-k-1)%ha;
            if((r[i]-k-1)&1) t = ha-t;
            (h[i] += t) %= ha;
        }
//        DEBUG(h[i]);DEBUG(chk);
//        assert(h[i]==chk);
    }
    FOR(i,1,n){
        g[i] = C(n-1,i);
        FOR(j,1,m){
            g[i] = 1ll*g[i]*h[j]%ha*C(n-i-1,n-i-r[j])%ha;
        }
    }
    int ans = 0;
    FOR(i,k,n){
        int t = 1ll*C(i,k)*g[i]%ha;
        if((i-k)&1) t = ha-t;
        (ans += t) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}

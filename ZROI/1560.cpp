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

const int MAXN = 3e6 + 5;
const int ha = 998244353;
int fac[MAXN],inv[MAXN];

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

inline int C(int n,int m){
	if(n < 0 || m < 0 || n < m) return 0;
	return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int n,ans = 0;

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int main(){
	prework();
	scanf("%d",&n);
	FOR(i,1,n){// i个0段
		// 分成i-1个1段
		// 000 ... 000
		int c2 = n-i+n-(i-1);c2 = n-c2;
		add(ans,1ll*C(n-1,i-1)*C(n-1,i-2)%ha*C(i+(i-1)+1,c2)%ha);
		// 分成i个1段
		// 2*(111 .... 0000)
		c2 = n-i+n-i;c2 = n-c2;
		add(ans,2ll*C(n-1,i-1)%ha*C(n-1,i-1)%ha*C(i+i+1,c2)%ha);
		// 分成i+1个1段
		// 111 ... 111
		c2 = n-i+n-(i+1);c2 = n-c2;
		add(ans,1ll*C(n-1,i-1)*C(n-1,i)%ha*C(i+i+1+1,c2)%ha);
	}
	printf("%d\n",ans);
	return 0;
}
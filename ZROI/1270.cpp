#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <cassert>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000;
const int ha = 998244353;
LL n;int a,b,c,d;
int f[MAXN];
int mod;
struct Matrix{
	int a[2][2];

	Matrix operator * (const Matrix &b) const{
		Matrix ret;CLR(ret.a,0);
		FOR(i,0,1){
			FOR(j,0,1){
				FOR(k,0,1){
					(ret.a[i][j] += 1ll*a[i][k] * b.a[k][j]%mod) %= mod;
				}
			}
		}
		return ret;
	}
}fib,ans;

inline LL gcd(LL x,LL y){
	return !y ? x : gcd(y,x%y);
}

namespace Subtask1{
	inline void Solve(){
		printf("%lld\n",gcd(1ll*a*f[n]+1ll*b*f[n+1],1ll*c*f[n]+1ll*d*f[n+1]));
	}
}

inline int F(LL n,int mod){
	::mod = mod;
	CLR(ans.a,0);CLR(fib.a,0);
	ans.a[0][0] = ans.a[1][1] = 1;
	fib.a[0][1] = fib.a[1][0] = fib.a[1][1] = 1;n--;
	while(n){
		if(n&1) ans = ans*fib;
		fib = fib*fib;n >>= 1;
	}
	return ans.a[1][1];
}

namespace Subtask2{
	inline void Solve(){
		// DEBUG(1);
		printf("%lld\n",1ll*F(n,ha)*gcd(a,c)%ha);
	}
}

namespace Subtask3{//b=0 c=0
	inline void Solve(){
		if(a == 0){
			printf("%lld\n",1ll*d*F(n+1,ha)%ha);
			return;
		}
		if(d == 0){
			printf("%lld\n",1ll*a*F(n,ha)%ha);
			return;
		}
		int g = gcd(a,d);a /= g;d /= g;
		int ans = 1ll*gcd(a,F(n+1,a))*gcd(d,F(n,d))%ha;
		printf("%lld\n",1ll*ans*g%ha);
	}
}

namespace Subtask4{

	void ggd(int a,int b,int c,int d){
		if(!c){
			::a = a;::b = b;::c = c;::d = d;
			return;
		}
		ggd(c,d,a%c,b-(a/c)*d);
	}

	inline void Solve(){
		ggd(a,b,c,d);
		c = d;// gcd(aF[n]+bF[n+1],cF[n+1])
		if(c < 0) c = -c;
		if(a < 0) a = -a,b = -b;
		// DEBUG(a);DEBUG(b);DEBUG(c);DEBUG(d);
		if(!c){
			int ans = 1ll*a*F(n,ha)%ha;
			(ans += 1ll*b*F(n+1,ha)%ha) %= ha;
			(ans += ha) %= ha;
			printf("%d\n",ans);
			return;
		}
		if(!a){
			int ans = gcd(b,c);
			ans = 1ll*ans*F(n+1,ha)%ha;
			(ans += ha) %= ha;
			printf("%d\n",ans);
			return;
		}
		if(!b){
			d = c;b = c = 0;
			Subtask3::Solve();
			return;
		}
		int g = gcd(a,F(n+1,a)),p = g*c;
		a = 1ll*a*F(n,p)%p;b = 1ll*b*F(n+1,p)%p;
		(a += p) %= p;(b += p) %= p;
		g = gcd((a+b)%p,p)%ha;
		// DEBUG(a);DEBUG(b);
		printf("%d\n",(g+ha)%ha);
	}
}

inline void Solve(){
	scanf("%lld%d%d%d%d",&n,&a,&b,&c,&d);
	if(n <= 10) Subtask1::Solve();
	else if(!b && !d) Subtask2::Solve();
	else if(!b && !c) Subtask3::Solve();
	else Subtask4::Solve();
}

signed main(){
	f[0] = 0;f[1] = 1;
	FOR(i,2,11) f[i] = (f[i-1]+f[i-2])%ha;
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
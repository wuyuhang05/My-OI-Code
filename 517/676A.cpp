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
#define FOR(i,a,b) for(LL i = a;i <= b;++i)
#define ROF(i,a,b) for(LL i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000;
LL k;

inline LL get(LL n){
	int res = 0;
	while(n) res += (n%10)*(n%10),n /= 10;
	return res; 
}

inline LL query(LL x){
	int ans = 0;
	FOR(fn,0,2000){
		LL n = fn*k;
		ans += (n <= x && fn==get(n));
	}
	return ans;
}

int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	LL a,b;scanf("%lld%lld%lld",&k,&a,&b);
	printf("%lld\n",query(b)-query(a-1));
	return 0;
} 

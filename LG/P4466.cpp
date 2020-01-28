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

const int MAXN = 1e6 + 5;

bool p[MAXN];
int prime[MAXN],cnt,mu[MAXN];
inline void prework(){
	mu[1] = 1;
	FOR(i,2,MAXN-1){
		if(!p[i]) prime[++cnt] = i,mu[i] = -1;
		for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
			p[i*prime[j]] = 1;mu[i*prime[j]] = -mu[i];
			if(!(i%prime[j])){
				mu[i*prime[j]] = 0;
				break;
			}
		}
	}
}

inline LL calc(int x,int y){
	if(!y) return 0;
	int lim = x*2;
	int ans = 0;
	for(int i = x+1;i < lim;i = x+1){
		if(!(y/i)) return ans;
		x = std::min(lim-1,y/(y/i));
		ans += (x-i+1)*(y/i);
	}
	return ans;
}

int main(){
	prework();
	int n;scanf("%d",&n);
	int q = std::sqrt(1.0*n);
	LL ans = 0;
	FOR(d,1,q){
		if(!mu[d]) continue;
		for(int i = 1;i*d <= q;++i){
			ans += mu[d]*calc(i,n/i/d/d);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
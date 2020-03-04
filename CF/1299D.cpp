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
#define int LL
signed main(){
	int T;scanf("%lld",&T);
	while(T--){
		int n,g,b;scanf("%lld%lld%lld",&n,&g,&b);
		int lim = (n+1)/2;
		int ans = 0;
		if(lim <= g){
			printf("%d\n",n);
			continue;
		}
		lim -= g;ans += g;int t = ((lim-1)/g)+1;
		ans += (((lim-1)/g)+1)*(g+b);
		if(t*b >= n-lim){
			printf("%d\n",ans);
			continue;
		}
		int tt = n-lim;tt -= t*b;
		
	}
	return 0;
}
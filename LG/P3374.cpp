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
const int MAXN = 2e6 + 5;
int sm[MAXN],a[MAXN];

int n,m;
int N = 1;

inline void modify(int x,int y){
	sm[x+=N] += y;
	for(x>>=1;x;x>>=1){
		sm[x] = sm[x<<1]+sm[x<<1|1];
	}
}

inline int query(int l,int r){
	int ans = 0;
	for(l += N-1,r += N+1;l^r^1;l>>=1,r>>=1){
		// DEBUG(l);DEBUG(r);
		// DEBUG((l^1));DEBUG((r^1));
		if(!(l&1)) ans += sm[l^1];
		if(r&1) ans += sm[r^1];
	}
	return ans;
}

signed main(){
	scanf("%lld%lld",&n,&m);
	while(N <= n) N<<= 1;
	FOR(i,1,n) scanf("%lld",a+i),sm[i+N] = a[i];
	ROF(i,N-1,0) sm[i] = sm[i<<1]+sm[i<<1|1];
	FOR(i,1,m){
		int opt,x,y;
		scanf("%lld%lld%lld",&opt,&x,&y);
		if(opt == 1){
			modify(x,y);
		}
		else printf("%lld\n",query(x,y));
	}
	return 0;
}
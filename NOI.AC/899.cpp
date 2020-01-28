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

const int MAXN = 8e6 + 5;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

short sm[MAXN<<2];
int n,N,m;

inline int plus(int x,int y){
	int res = 0;
	FOR(i,0,12){
		if((x>>i)&1){
			res ^= (y<<i);
		}
	}
	return (res&((1<<13)-1))^(res>>13);
}

inline void update(int x){
	x += N;
	for(x >>= 1;x;x >>= 1){
		sm[x] = plus(sm[lc],sm[rc]);
	}
}

inline int query(int l,int r){
	int res = 1;
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) res = plus(res,sm[l^1]);//,DEBUG(sm[l^1]);
		if(r&1) res = plus(res,sm[r^1]);//,DEBUG(sm[r^1]);
	}
	return res;
}

inline int get(char x){
	if(!isdigit(x)) return 10+(x-'a');
	else return x-'0';
}

inline int calc(int x){
	FOR(i,1,13) if((x>>i)&1) return i;
}

char str[MAXN];

int main(){
	// int sz = sizeof(sm);
	// DEBUG(sz/1024/1024);
	scanf("%d%d",&n,&m);
	N = 1;while(N <= n) N <<= 1;scanf("%s",str+1);
	FOR(i,1,n){
		sm[i+N] = 1|(1<<(get(str[i])));
	}
	ROF(x,N-1,0) sm[x] = plus(sm[lc],sm[rc]);
	FOR(i,1,m){
		int l,r;scanf("%d%d",&l,&r);
		int res = query(l,r);
		FOR(i,0,12) putchar('0'+((res>>i)&1));
		int ll = calc(sm[l+N]),rr = calc(sm[r+N]);
		ll = std::max((ll+1)%13,1);
		rr = std::max((rr+1)%13,1);
		sm[l+N] = 1|(1<<ll);
		sm[r+N] = 1|(1<<rr);
		update(l);update(r);
		puts("");
	}
	return 0;
}
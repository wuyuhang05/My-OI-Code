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

const int MAXN = 1e5 + 5;
LL smi[MAXN<<2],sm[MAXN<<2];
int a[MAXN];
int n,m,N;

inline void build(){
	FOR(i,1,n) smi[i+N] = 1ll*a[i]*(i-1),sm[i+N] = a[i];
	ROF(i,N,0) smi[i] = smi[i<<1]+smi[i<<1|1],sm[i] = sm[i<<1]+sm[i<<1|1];
}

inline void update(int x,int d){
	smi[x+N] = 1ll*d*(x-1);sm[x+=N] = d;
	for(x >>= 1;x;x >>= 1){
		sm[x] = sm[x<<1]+sm[x<<1|1];
		smi[x] = smi[x<<1]+smi[x<<1|1];
	}
}

inline LL query(int l,int r){
	LL res = 0;
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) res += sm[l^1];
		if(r&1) res += sm[r^1];
	}
	return res;
}

inline LL queryi(int l,int r){
	LL res = 0;
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) res += smi[l^1];
		if(r&1) res += smi[r^1];
	}
	return res;
}

char str[10];

int main(){
	// freopen("a.in","r",stdin);
	// freopen("a.out","w",stdout);
	scanf("%d%d",&n,&m);N = 1;
	while(N <= n) N <<= 1;
	FOR(i,1,n) scanf("%d",a+i);
	build();
	FOR(i,1,m){
		scanf("%s",str);
		if(str[0] == 'Q'){
			int x;scanf("%d",&x);
			printf("%lld\n",1ll*x*query(1,x)-queryi(1,x));
		}
		else{
			int p,d;scanf("%d%d",&p,&d);
			update(p,d);
		}
	}
	return 0;
}
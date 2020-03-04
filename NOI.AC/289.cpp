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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e6 + 5;
P a[MAXN];//<t,x>
int f[MAXN],n,N;
int g[MAXN];
int top = 0;
// f 单调 t 单调

int mn[MAXN<<2];

inline void update(int pos,int x){
	for(pos += N;pos;pos >>= 1) mn[pos] = std::min(mn[pos],x);
}

inline int query(int l,int r){
	if(l > r) return 1e18;int res = 1e18;
	for(l += N-1,r += N+1;l^r^1;l >>= 1,r >>= 1){
		if(!(l&1)) res = std::min(res,mn[l^1]);
		if(r&1) res = std::min(res,mn[r^1]);
	}
	return res;
}

signed main(){
	// DEBUG(1);
	scanf("%lld",&n);
	FOR(i,1,n) scanf("%lld%lld",&a[i].fi,&a[i].se);
	std::sort(a+1,a+n+1);
	FOR(i,1,n){
		while(top && a[top].se < a[i].se) top--;
		a[++top] = a[i];
	}
	n = top;f[1] = a[1].fi+2*a[1].se;
	CLR(mn,0x3f);N = 1;while(N <= n) N <<= 1;
	update(1,f[1]+2*a[2].se);
	FOR(i,2,n){
		f[i] = 1e18;
		int p = std::upper_bound(f,f+i,a[i].fi)-f;
		if(p >= 0) f[i] = std::min(f[i],a[i].fi+2*a[p].se);
		// DEBUG(f[i]);
		// DEBUG(query(p,i-1));
		f[i] = std::min(f[i],query(p,i-1));
		// DEBUG(f[i]);
		update(i,f[i]+2*a[i+1].se);
	}
	// FOR(i,1,n) printf("%lld ",f[i]);puts("");
	printf("%lld\n",f[n]);
	return 0;
}
/*
考虑按照t 排序 然后设 f[i] 表示前 i 个人都处理完了  枚举最后一群一起处理的人:
f[i] = min{max{f[j],t[i]}+2*max(x[j+1~i])}
发现如果 x[i] <= x[i+1] 那么把 i 和 i+1 合并会更优 所以我们现在默认 x[i] 不增
又观察到 f[i] 增 所以我们分类讨论 max{f[j],t[i]} 的取值 满足条件的一定是一段区间:
设第一个满足 f[j] > t[i] 的位置为 p
1. f[i] = min{t[i]+2*x[j+1]} j <= p 取尽量靠后的位置
2. f[i] = min{f[j]+2*x[j+1]} j > p 可以用数据结构维护求最小值
*/

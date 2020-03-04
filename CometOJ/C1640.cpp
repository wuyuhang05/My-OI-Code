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

const int MAXN = 100+5;
int val[MAXN],lc[MAXN],rc[MAXN],a[MAXN],l[MAXN],r[MAXN],n,k;
int f[MAXN][MAXN][MAXN]; // 在点 v 切了 i 刀 上一次在 深度 j 切
int st[MAXN],tp,rt;

inline void dfs(int v){
	l[v] = r[v] = v;
	if(lc[v]){
		dfs(lc[v]);
		l[v] = l[lc[v]];
	}
	if(rc[v]){
		dfs(rc[v]);
		r[v] = r[rc[v]];
	}
}

inline void build(){
	FOR(i,1,n){
		int pre = 0;
		while(tp && val[st[tp]] > val[i]){
			pre = st[tp];tp--;
		}
		if(!tp) rt = i;
		else rc[st[tp]] = i;
		lc[i] = pre;st[++tp] = i;
	}
	dfs(rt);
}

inline int dp(int v,int i,int j){ // fa = j
	if(!v) return 0;
	if(f[v][i][j] != -1) return f[v][i][j];
	int &res = f[v][i][j];res = 0;
	FOR(k,0,i) res = std::max(res,dp(lc[v],k,j)+dp(rc[v],i-k,j));
	FOR(k,0,i-1) res = std::max(res,dp(lc[v],k,v)+dp(rc[v],i-k-1,v)+(r[v]-l[v]+1)*(val[v]-val[j]));
	return res;
}

int main(){
	scanf("%d%d",&n,&k);CLR(f,-1);
	FOR(i,1,n) scanf("%d",val+i);
	build();
	printf("%d\n",dp(rt,k,0));
	return 0;
}
/*
看到 n 这么小就可以考虑区间 dp 了
考虑每次切肯定尽量切最大的一块 也就是类似于短板原理 总是由区间的最小值限制
设 f[l][r][i] 表示区间[l,r]被切了 i 次的最小代价 每次一定是选最小值分割下去
所以实际上是在笛卡尔树上dp.我们建出笛卡尔树之后可以设 f[v][i] 表示 v 子树内切了 i 次的代价.
接下来我们发现这一次切割可能会对之后的切割有些影响:因为下面的那些已经被切没了. 所以对于每个状态 我们需要加一维记录最近的一次是在哪里切的 把多余的贡献减去即可
转移枚举这个点切不切 枚举左子树右子树切多少下即可
O(n^4) 但是由于区间 dp 的小常数跑的飞快
*/
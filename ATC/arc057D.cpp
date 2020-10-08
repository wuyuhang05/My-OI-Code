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

const int ha = 1e9 + 7;
const int MAXN = 30+5;
int n;
int a[MAXN*MAXN];

std::map<std::vector<int>,int> f[MAXN*MAXN][MAXN*MAXN];

inline int dp(int i,int j,std::vector<int> S){
	if(i == 1+n*(n-1)/2) return 1;
	if(f[i][j].count(S)) return f[i][j][S];
	int &res = f[i][j][S];res = 0;
	if(a[i]){
		FOR(x,0,(int)S.size()-1){
			FOR(y,x+1,(int)S.size()-1){
				std::vector<int> nxt;
				FOR(k,0,(int)S.size()-1) if(k != x && k != y) nxt.pb(S[k]);
				nxt.pb(S[x]+S[y]);std::sort(all(nxt));
				(res += 1ll*S[x]*S[y]%ha*dp(i+1,j+S[x]*S[y]-1,nxt)%ha) %= ha;
			}
		}
	}
	else{
		if(j) res = 1ll*j*dp(i+1,j-1,S)%ha;
	}
	return res;
}

int main(){
	scanf("%d",&n);
	FOR(i,2,n){
		int x;scanf("%d",&x);a[x] = 1;
	}
	std::vector<int> S;
	printf("%d\n",dp(1,0,std::vector<int>(n,1)));
	return 0;
}
/*
这其实也是一类 dp of sth. 的东西 我们要先学会如果解决 sth.(判定性问题)然后解决 dp
考虑 Kruskal 做生成树的过程
一个暴力的想法是转移时把所有并查集的状态记录下来 这样状态数就是优秀的 O(n^n) 啦
但是我们发现我们其实不需要真的记录每块的编号啥的 我们其实只需要记录每个连通块的大小即可 状态数就是划分数了(5604)
设 f[i][j][S] 表示考虑到 i 条边 有 j 个边加入后不改变连通性 当前并查集的状态为 S
如果这条边不能成为树边 那么有转移 j*f[i][j][S] -> f[i+1][j-1][S]
如果要成为树边 枚举合并哪两个连通块(大小为 x,y)并处理处合并后的新状态 S' xyf[i][j][S] -> f[i+1][j+xy-1][S']
如果是直接这样 O(n^2) 枚举转移就不用乘组合数了 如果是枚举 size 种类数需乘组合数
*/
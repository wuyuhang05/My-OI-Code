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

const int MAXN = 600+5;
int a[MAXN],n,m;
int f[MAXN][MAXN][MAXN];
int A[MAXN],B[MAXN];
bool fs[MAXN];

int main(){
	scanf("%d",&m);
	FOR(i,1,m){
		int x,y;scanf("%d%d",&x,&y);
		if(x != -1 && y != -1) continue;
		a[++n] = x;a[++n] = y;
	}
	FOR(i,1,n) A[i] = A[i-1]+(a[i] != -1);
	FOR(i,1,n) B[i] = B[i-1]+((!(i&1)) && (a[i]==-1||a[i-1]==-1));
	FOR(i,1,n) if(a[i] != -1) fs[a[i]] = 1;
	FOR(i,1,n){
		FOR(j,1,n){
			FOR(k,1,n){
				int l = (A[i]+B[i]+k-j)/2;

			}
		}
	}
	return 0;
}
/*
考虑我们加入一个数的时候 可能加入到一个空 pair 可能加入到一个含有一个元素的的 pair ,其中要考虑这个元素和当前数的关系 把这些东西都记下来
设 f[i][j][k][l] 表示从小到大加入了前 i 个数字 保留了 j 个数字 有 k 个需要一个大的数 填了 l 个空着的 pair
记空 pair 的个数为 cnt
**因为这里你如果把一个数字当做最小值插入 你不太清楚用哪个数字匹配 我们可以限制所有 pair 在最大值插入后统计答案 这是一种比较常见的做法(可惜我不会)
1. 这个数出现过
	1.1 这个数字所在的 pair 填满了 直接跳过
	1.2 这个数字所在的 pair 有一个数字没补全 你需要决定那个数字填什么
		1.2.1 这个数字作为较小值 f[i][j][k][l] -> f[i+1][j][k+1][l]
		1.2.2 这个数字作为较大值 f[i][j][k][l]*j -> f[i+1][j-1][k][l]
2. 这个数没出现过
	2.1 这个数放在一个空 pair 里 f[i][j][k][l]*(cnt-l) -> f[i+1][j][k+1][l+1]
	2.2 这个数放在一个有一个数的 pair 里
		2.2.1 这个数作为较小值 f[i][j][k][l] -> f[i+1][j+1][k][l]
		2.2.2 这个数作为较大值 f[i][j][k][l] -> f[i+1][j][k-1][l]
		这里不加系数 因为较大值放在哪里都无关紧要 较小值的系数会在1.2.2统计到
核心思想还是对于每个 pair 都考虑 在填最大值的时候从 dp 值中抓一个匹配的值算上方案 作为最小值的时候只需要增加 dp 维度就可以了
这样的复杂度是 O(n^4) 的,很垃圾 考虑是否能压缩状态?
观察 dp 转移方程(2) 可以发现
l = (A+B+k-j)/2
所以滚掉最后一维
先咕了
*/
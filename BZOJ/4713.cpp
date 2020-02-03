/*
对于单独的一个字符串 我们设 f[v][i] 表示到达 v 边是否可以匹配到字符串的第 i 位
转移 f[v][i]&(w[fe[v]]==str[i+1]) -> f[fe[v]][i+1]
然后正反串都做一遍 判断一下就好了
考虑 bitset 优化 把第二维压起来
转移的时候 (f[v]<<1)*u[w[fe[v]]] -> f[fe[v]] 还需要处理下 f[v][0,1]
u[v][i] 表示第 i 位是不是 v 这个字母
这样复杂度是 O(n*sumlen/w)
最后查询的时候就枚举一下 lca,and 一下看看是否为空就行了 复杂度也是对的
 */
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

const int MAXN = 30000+5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
}

int main(){

	return 0;
}
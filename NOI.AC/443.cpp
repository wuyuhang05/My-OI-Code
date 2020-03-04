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

int main(){
	return 0;
}
/*
首先 min-max 容斥变成求 m 个人中第一次出现有一个人的数量 >= k 的期望次数
可以考虑求出恰好在第 i 次结束的概率 
f[m][i] 表示 m 个人在 i 次不结束的概率
g[m][i] 表示 m 个人在 i 次不结束的方案数
h[m][i] 表示 m 个人在 i 次恰好结束的方案数
f[m][i] = f[m][i-1]*(g[m][i]/(g[m][i]+h[m][i]))
h[m][i] = g[m-1][i-k]*C(i-1,k-1)*m
g 的计算考虑枚举某个人的苹果数
g[m][i] = \sum_{j=0}^{k-1} g[m-1][i-j]*C(i,j)
考虑 m 个人第一次出现有一个人的数量 >= k 的期望次数 F[m] 如何计算:
F[m] = \sum_{i=1}^{m*k} i*((h[m][i])/(g[m][i]+h[m][i]))
最后答案就是
ans = \sum_{i=1}^n C(n,i)*F[i]*(-1)^{i-1} *(n/i)
:TODO 代码先咕着
*/
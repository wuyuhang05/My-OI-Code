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
    // TODO: 写代码（估计咕咕到退役）
    return 0;
}
/*
排列性问题 涉及到大小问题 要考虑从小往大插：
考虑如果按顺序现在插入一个数 x 它左右每一个未填的空会贡献-x，每一个已填的空会贡献+x
对于贴近左右边界的连续块需要特殊处理
所以记 f[i][j][k][l] 填了前 i 个数 答案是 j ，有 k 段中间的连续段 l 段贴边界的连续段
分类讨论：考虑插入 i+1 
1. i+1 单独成段 
    1.1 i+1 在中间f[i][j][k][l]*(k+1) -> f[i+1][j-2*(i+1)][k+1][l]
    1.2 i+1 在边上f[i][j][k][l]*(2-l) -> f[i+1][j-(i+1)][k][l+1]
2. i+1 和之前并起来了
    2.1 i+1 单独和边界并起来了 f[i][j][k][l]*l -> f[i+1][j][k][l]
    2.2 i+1 单独和中间并起来了 f[i][j][k][l]*2k -> f[i+1][j][k][l]
    2.3 i+1 连接了中间两块 f[i][j][k][l]*(k-1) -> f[i+1][j+2*(i+1)][k-1][l]
    2.4 i+1 连接了边界和中间 f[i][j][k][l]*l -> f[i+1][j+2*(i+1)][k-1][l]
由于需要实现高精度小数 所以不写了。
*/

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

const int MAXN = 1e6 + 5;
const int ha = 1e9 + 7;
int n,m;
int f[MAXN],sm[MAXN];
int t[MAXN*2+233];

int main(){
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int x;scanf("%d",&x);sm[x]++;
    }
    FOR(i,1,n) sm[i] += sm[i-1];
    f[0] = 1;int ans = 0;
    t[sm[0]-1+MAXN]++;
    FOR(i,1,n){
        if(sm[i]-sm[i-1] != 0) continue;
        (f[i] += t[sm[i-1]-i+MAXN])%=ha;
        (t[sm[i]-i-1+MAXN] += f[i])%=ha;
    }
    ROF(i,n,0){
        if(sm[i]-sm[i-1] != 0) continue;
        if(sm[n]-sm[i] == n-i) (ans += f[i]) %= ha;
    }
    // FOR(i,1,n) printf("%d ",f[i]);puts("");
    printf("%d\n",ans);
    return 0;
}
/*
一类插入性dp可以从最终结果入手
发现最终结果是一段一段的连续段 空格子隔开了所有的连续段 所以我们可以考虑对空格子dp
设 f[i] 表示第 i 个位置为空的方案数，考虑枚举上一个为空的位置 j 
我们先预处理出 S[i] 表示第 i 个位置落下的方块个数， sm[i] 表示前 i 个位置落下的方块个数
考虑 i-1 怎么填：如果 S[i-1] 为0 显然有转移f[i-1]->f[i]
否则 i-1 要填上 我们枚举上一个空格 j 那么f[j]->f[i] if sm[i-1]-sm[j] == i-j-1
整理得到 sm[i-1]-i = sm[j]-j-1 可以用一个桶优化转移
统计答案的时候枚举最后一段的长度就可以了。
*/
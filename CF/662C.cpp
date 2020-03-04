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
#define int LL
const int MAXN = (1<<21)+3;
char str[21][MAXN];
int n,m,N;
int D[MAXN],A[MAXN],pc[MAXN];

inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = x+y;
                f[i+mid+j] = x-y;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)/2;
                f[i+mid+j] = (x-y)/2;
            }
        }
    }
}

signed main(){
    scanf("%lld%lld",&n,&m);N = (1<<(n+1));
    FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+(i&1);
    FOR(i,1,n) scanf("%s",str[i]+1);
    FOR(j,1,m){
        int zt = 0;
        FOR(i,1,n){
            if(str[i][j] == '1') zt |= (1<<(i-1));
        }
        D[zt]++;
    }
    FOR(S,0,(1<<n)-1) A[S] = std::min(pc[S],n-pc[S]);
    FWT(A);FWT(D);
    FOR(i,0,N-1) A[i] = A[i]*D[i];
    iFWT(A);
    int ans = 1e18;
    FOR(i,0,(1<<n)-1) ans = std::min(ans,A[i]);
    printf("%lld\n",ans);
    return 0;
}
/*
考虑如果行如何翻转定下来之后 就可以简单统计答案了：每行1和0的值取min
所以我们枚举哪些行操作了 设操作的行状态为 S ，答案是 f[S]，那么对于某一列的状态 T 新状态应该是 S xor T
预处理每一种状态在多少列中出现 D[S]，每一列的答案 A[S]， D[T]*A[S xor T] -> f[S];
用 S xor T -> S 得到
D[T]*A[S] -> f[S xor T] FWT优化即可
*/
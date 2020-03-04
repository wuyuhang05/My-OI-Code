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

const int MAXN = 5e6 + 5;
int f[MAXN],a[MAXN];
int n,N,MX;

inline void FWT(){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                f[i+j] = std::min(f[i+j],f[i+mid+j]);
            }
        }
    }
}
int sm[MAXN];
int main(){
    scanf("%d",&n);int mx = 0;
    FOR(i,1,n) scanf("%d",a+i),sm[i] = sm[i-1]^a[i],mx = std::max(mx,a[i]);
    N = 1;while(N <= mx) N <<= 1,++MX;N <<= 1;
    FOR(i,0,N-1) f[i] = 1e9;
    FOR(i,1,n) f[sm[i]] = std::min(f[sm[i]],i);
    FWT();
    // FOR(i,0,n) printf("%d ",sm[i]);puts("");
    FOR(i,1,n){
        int ans = sm[i],t = 0;
        ROF(j,MX,0){
            if((sm[i]>>j)&1) continue;
            // if(i == 2) DEBUG((t|(1<<j))),DEBUG(f[t|(1<<j)]);
            if(f[t|(1<<j)] <= i) t |= (1<<j);
        }
        // if(i == 2) DEBUG(t);
        ans += 2*t;
        printf("%d ",ans);
    }
    puts("");
    return 0;
}
/*
遇到异或和加法的时候尝试把加法去掉 加法和位运算那一套不太合得来
(a+b) = (a xor b)+2(a and b)
最大值问题可以从高往低考虑+真值表判断贡献+FWT预处理是否可行
*/
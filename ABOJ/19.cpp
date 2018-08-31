#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

int N;
int bit[100],x;
const int ha = 998244353;

int main(){
    scanf("%d",&N);
    FOR(i,1,N){
        scanf("%d",&x);
        FOR(j,0,31)
            bit[j] += (x & (1 << j)) ? 1 : 0;
    }
    U LL ans = 0;
    FOR(i,1,N){
        U LL x = 0;
        FOR(j,0,31)
            if(bit[j]){
                x |= (1 << j);
                bit[j]--;
            }
        ans += (x*x)%ha;
    }
    ans %= ha;
    printf("%llu\n",ans%ha);
    return 0;
}

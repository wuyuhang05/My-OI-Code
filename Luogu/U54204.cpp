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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

LL x;

inline void Solve(){
    scanf("%lld",&x);
    if(x < 0){
        puts("-1");
        return;
    }
    LL q = std::sqrt(x);
    LL a=1,b=x;
    FOR(i,1,q){
        if(!(b%(i*i))){
            b /= (i*i);
            a *= i;
        }
    }
    printf("%lld %lld\n",a,b);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

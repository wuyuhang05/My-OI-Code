#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define RFOR(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int Q;
const int ha = 9;

inline LL qpow(LL a,LL n){
    LL ret = 1;
    while(n){
        if(n & 1) ret = (ret * a)%ha;
        a = (a * a) % ha;
        n >>= 1;
    }
    return ret % ha;
}

inline LL f(LL n){
    LL a = n,b = n+1;
    if(a & 1) b /= 2;
    else a /= 2;
    LL ret = (a%9)*(b%9);
    return ret%9;
}

int main(){// std::cout << qpow(2,7) << std::endl;
    scanf("%d",&Q);
    while(Q--){
        LL l,r;
        scanf("%lld%lld",&l,&r);
        LL ans = f(r) - f(l-1);
        printf("%lld\n",(ans + ha)%ha);
    }
    return 0;
}
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

LL N,A,B,C,D;

int main(){
    scanf("%lld%lld%lld%lld%lld",&N,&A,&B,&C,&D);
    FOR(k,0,N-1){
        if(k*C-(N-k-1)*D <= B-A && B-A <= k*D-(N-k-1)*C){
            puts("YES");
            return 0;
        }
    }
    puts("NO");
    return 0;
}

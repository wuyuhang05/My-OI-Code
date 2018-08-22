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

#define LL long long
#define U unsigned
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int ha = 998244353;
int N,M;

LL qpow(LL a,LL n){
    LL ret = 1;
    while(n){
        if(n&1) ret = (ret * a) % ha;
        a = (a*a)%ha;
        n >>= 1;
    }
    return ret;
}

int main(){
    scanf("%d%d",&N,&M);
    LL f1=1,f2=1;
    for(int i = M+1;i <= N + M - 1;i++) f1 = (f1*i) % ha;
    for(int i = 1;i < N;i++) f2 = (f2 * i) % ha;
    printf("%lld\n",f1%ha*qpow(f2,ha-2)%ha);
    return 0;
}

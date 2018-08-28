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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

int presum[MAXN];

inline int six(int x){
    int ret = 0;
    while(x){
        if(x % 6 == 1) ret++;
        x /= 6;
    }
    return ret;
}

inline int nine(int x){
    int ret = 0;
    while(x){
        if(x % 9 == 1) ret++;
        x /= 9;
    }
    return ret;
}

inline void pre(){
    FOR(i,1,MAXN)
        presum[i] = presum[i-1] + ((std::abs(six(i)-nine(i)) <= 1) ? 1 : 0);
}

int main(){
    int T;
    pre();
    scanf("%d",&T);
    while(T--){
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",presum[r] - presum[l-1]);
    }
    return 0;
}

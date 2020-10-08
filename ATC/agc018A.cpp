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

int N,K;
int g,max;

int gcd(int x,int y){
    return (!y) ? x : gcd(y,x%y);
}

int main(){
    scanf("%d%d",&N,&K);
    FOR(i,1,N){
        int x;scanf("%d",&x);max = std::max(max,x);
        if(i == 1) g = x;
        else g = gcd(g,x);
    }
    if(K%g || K > max) puts("IMPOSSIBLE");
    else puts("POSSIBLE");
    return 0;
}

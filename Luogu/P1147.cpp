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

const int MAXN = 2000000 + 5;

LL sum[MAXN];

int main(){
    int M;
    scanf("%d",&M);
    FOR(i,1,M)
        sum[i] = sum[i-1] + i; 
    int j = 1; 
    FOR(i,1,M){
        while(sum[j]-sum[i-1] < M) j++; 
        if(sum[j]-sum[i-1] == M && i != j){ 
            printf("%d %d\n",i,j);
        } 
    }
    return 0;
}

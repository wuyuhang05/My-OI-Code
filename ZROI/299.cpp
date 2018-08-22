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
const int MAXK = 20 + 5;

int N,K;
int a[MAXN];
int f[MAXN][MAXK],w[MAXN][MAXN];

int main(){
    scanf("%d%d",&N,&K);
    FOR(i,1,N)
        scanf("%d",a+i);
    for(i,1,N)
        for(j,0,K)
            f[i][j] = INT_MAX;

    return 0;
}

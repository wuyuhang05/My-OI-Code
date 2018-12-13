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
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000+5;
const int MAXS = 10+5;

int N;
int f[MAXN][MAXS],cnt[MAXN][MAXS];

inline void Solve(){
    CLR(f,0);
    int mx=0;
    FOR(i,1,N){
        int x,T;scanf("%d%d",&x,&T);
        f[T][x]++;mx = std::max(mx,T);
    }
    ROF(i,mx-1,0){
        FOR(j,0,10){
            f[i][j] += std::max(f[i+1][j-1],std::max(f[i+1][j],f[i+1][j+1]));
        }
    }
    printf("%d\n",f[0][5]);
}

int main(){
    scanf("%d",&N);
    while(N){
        Solve();
        scanf("%d",&N);
    }
    return 0;
}
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

const int MAXN = 100 + 5;

int N,M,ans;
int f[MAXN][MAXN],a[MAXN][MAXN];

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) FOR(j,1,M) scanf("%d",&a[i][j]);
    FOR(i,1,N) FOR(j,1,M) if(a[i][j]) {f[i][j] = std::min(f[i-1][j],std::min(f[i][j-1],f[i-1][j-1]))+1;ans = std::max(ans,f[i][j]);};
    printf("%d\n",ans);
    return 0;
}

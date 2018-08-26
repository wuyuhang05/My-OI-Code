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

const int MAXN = 100 + 5;
const int MAXM = 10000 + 5;

int f[MAXN][MAXN];
int N,M;
int l[MAXM];

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,M)
        scanf("%d",l+i);
    CLR(f,0x3f);
    FOR(i,1,N)
        FOR(j,1,N)
            scanf("%d",&f[i][j]);
    FOR(k,1,N)
        FOR(i,1,N)
            FOR(j,1,N)
                f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
    int ans = 0;
    FOR(i,2,M){
        ans += f[l[i-1]][l[i]];
    }
    printf("%d\n",ans);
    return 0;
}

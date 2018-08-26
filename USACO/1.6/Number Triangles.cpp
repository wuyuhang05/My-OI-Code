/*
ID: wuyuhan5
PROB: numtri
LANG: C++
*/
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

const int MAXN = 1000 + 5;
int N;
int a[MAXN][MAXN],f[MAXN][MAXN];

int main(){
    freopen("numtri.in","r",stdin);
    freopen("numtri.out","w",stdout);
    scanf("%d",&N);
    FOR(i,1,N)
        FOR(j,1,i)
            scanf("%d",&a[i][j]);
    FOR(i,1,N)
        f[N][i] = a[N][i];
    RFOR(i,N-1,1){
        FOR(j,1,i){
            f[i][j] = std::max(f[i+1][j],f[i+1][j+1])+a[i][j];
        }
    }
    printf("%d\n",f[1][1]);
    return 0;
}

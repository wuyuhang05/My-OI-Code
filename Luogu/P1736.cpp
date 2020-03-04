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

const int MAXN = 2500 + 5;
int N,M;
int s1[MAXN][MAXN],s2[MAXN][MAXN],f[MAXN][MAXN];
int a[MAXN][MAXN];

int ans = 0;

int main(){
    scanf("%d%d",&N,&M);
    FOR(i,1,N) FOR(j,1,M) scanf("%d",&a[i][j]);
    CLR(s1,0);CLR(s2,0);CLR(f,0);
    FOR(i,1,N){
        FOR(j,1,M){
            if(!a[i][j]){
                s1[i][j] = s1[i-1][j] + 1;
                s2[i][j] = s2[i][j-1] + 1;
            }
            else{
                f[i][j] = std::min(f[i-1][j-1],std::min(s1[i-1][j],s2[i][j-1]))+1;
                ans = std::max(ans,f[i][j]);
            }
        }
    }
    CLR(s1,0);CLR(s2,0);CLR(f,0);
    FOR(i,1,N){
        RFOR(j,M,1){
            if(!a[i][j]){
                s1[i][j] = s1[i-1][j] + 1;
                s2[i][j] = s2[i][j+1] + 1;
            }
            else{
                f[i][j] = std::min(f[i-1][j+1],std::min(s1[i-1][j],s2[i][j+1]))+1;
                ans = std::max(ans,f[i][j]);
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}

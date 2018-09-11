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

const int MAXN = 300 + 5;

int N,K;
int f[MAXN][MAXN][MAXN];
char str1[MAXN],str2[MAXN];

int main(){
    scanf("%d%d",&N,&K);
    scanf("%s%s",str1+1,str2+1);
    FOR(i,1,N){
        FOR(j,1,N){
            FOR(k,0,K){
                if(str1[i] == str2[j]) f[i][j][k] = std::max(f[i][j][k],f[i-1][j-1][k] + 1);
                if(k) f[i][j][k] = std::max(f[i][j][k],f[i-1][j-1][k-1] + 1);
            }
        }
    }
    int ans = 0;
    FOR(i,1,N) FOR(j,1,N) FOR(k,0,K) ans = std::max(ans,f[i][j][k]);
    printf("%d\n",ans);
    return 0;
}
/*
5 0
abcde
jcdkl
*/

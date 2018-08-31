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

const int MAXN = 200 + 5;
int f[MAXN][MAXN];

int N,M,T;
int m[MAXN],t[MAXN];

int main(){
    scanf("%d%d%d",&N,&M,&T);
    FOR(i,1,N)
        scanf("%d%d",m+i,t+i);
    FOR(i,1,N){
        RFOR(j,M,m[i]){
            RFOR(k,T,t[i]){
                f[j][k] = std::max(f[j][k],f[j-m[i]][k-t[i]]+1);
            }
        }
    }
    printf("%d\n",f[M][T]);
    return 0;
}

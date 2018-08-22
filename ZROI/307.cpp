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
double u,v,c[MAXN],d[MAXN];
int N;

int main(){
    scanf("%d%lf%lf",&N,&v,&u);
    FOR(i,1,N)
        scanf("%lf",c+i);
    FOR(i,1,N)
        scanf("%lf",d+i);
    double ans = 0.0;
    FOR(i,1,N)
        FOR(j,0,N-1)
            ans += (double)u/(c[i]-d[i] * j - v);
    printf("%.3f\n",ans);
    return 0;
}

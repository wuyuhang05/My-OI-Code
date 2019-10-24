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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const double EPS = 1e-7;
const int MAXN = 200+5;
double d[MAXN][MAXN],ans[MAXN];
int n;

int main(){
    scanf("%d",&n);
    FOR(i,1,n) FOR(j,1,n+1) scanf("%lf",&d[i][j]);
    FOR(i,1,n){
        int r = i;
        FOR(j,i+1,n) if(std::fabs(d[r][i]) < std::fabs(d[j][i])) r = j;
        if(std::fabs(d[r][i]) < EPS){
            puts("No Solution");
            return 0;
        }
        if(i != r) std::swap(d[r],d[i]);
        double div = d[i][i];
        FOR(j,i,n+1) d[i][j] /= div;
        FOR(j,i+1,n){
            div = d[j][i];
            FOR(k,i,n+1) d[j][k] -= d[i][k]*div;
        }
    }
    ans[n] = d[n][n+1];
    ROF(i,n-1,1){
        ans[i] = d[i][n+1];
        FOR(j,i+1,n) ans[i] -= (d[i][j]*ans[j]);
    }
    FOR(i,1,n) printf("%.2f\n",ans[i]);
    return 0;
}

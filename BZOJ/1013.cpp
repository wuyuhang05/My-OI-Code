/*
 * Time: 2019-11-29 19:57:50
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20+5;
double a[MAXN][MAXN];
int n;
double p[MAXN][MAXN],ans[MAXN];

inline void Gauss(){
    FOR(i,1,n){
        int tt = i;
        FOR(j,i+1,n){
            if(std::fabs(a[j][i]) > std::fabs(a[tt][i])) tt = j;
        }
        if(i != tt) std::swap(a[i],a[tt]);
        double t = a[i][i];
        FOR(j,i,n+1) a[i][j] /= t;
        FOR(j,i+1,n){
            t = a[j][i];
            FOR(k,i,n+1) a[j][k] -= a[i][k]*t;
        }
    }
    ans[n] = a[n][n+1];
    ROF(i,n-1,1){
        ans[i] = a[i][n+1];
        FOR(j,i+1,n) ans[i] -= a[i][j]*ans[j];
    }
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n+1) FOR(j,1,n) scanf("%lf",&p[i][j]);
    FOR(i,1,n){
        double sm = 0;
        FOR(j,1,n) sm += p[i][j]*p[i][j]-p[i+1][j]*p[i+1][j],a[i][j] = 2*(p[i][j]-p[i+1][j]);
        a[i][n+1] = sm;
    }
    Gauss();
    FOR(i,1,n) printf("%.3f ",ans[i]);puts("");
    return 0;
}

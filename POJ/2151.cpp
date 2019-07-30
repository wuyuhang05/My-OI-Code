/*
 * Author: RainAir
 * Time: 2019-07-13 15:26:36
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
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

double p[1001][31],f[1001][31][31],s[1001][31];
int n,m,t;

inline void init(){
    CLR(f,0);CLR(s,0);
    FOR(i,1,t){
        f[i][0][0] = 1.0;
        FOR(j,1,m) f[i][j][0] = f[i][j-1][0]*(1-p[i][j]);
        FOR(j,1,m){
            FOR(k,1,j){
                f[i][j][k] = f[i][j-1][k-1]*p[i][j]+f[i][j-1][k]*(1-p[i][j]);
            }
        }
        s[i][0] = f[i][m][0];
        FOR(j,1,m) s[i][j] = s[i][j-1]+f[i][m][j];
    }
}

inline void Solve(){
    FOR(i,1,t) FOR(j,1,m) scanf("%lf",&p[i][j]);
    init();
    double p1 = 1.0;
    FOR(i,1,t) p1 = 1ll*p1*(s[i][m]-s[i][0]);
    double p2 = 1.0;
    FOR(i,1,t) p2 *= (s[i][n-1]-s[i][0]);
    printf("%.3f\n",p1-p2);
}

int main(){
    while(~scanf("%d%d%d",&m,&t,&n)&&(n+m+t)) Solve();
    return 0;
}

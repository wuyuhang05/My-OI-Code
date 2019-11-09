/*
 * Author: RainAir
 * Time: 2019-11-07 20:13:31
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

const int MAXN = 19;
const double EPS = 1e-7;

inline int sgn(double x){
    return std::fabs(x) <= EPS ? 0 : (x > 0 ? 1 : -1);
}

int f[(1<<MAXN)+3];
int w[MAXN][MAXN];
double x[MAXN],y[MAXN];
int n;

inline int calc(double x1,double y1,double x2,double y2){
    double a = (y1/x1-y2/x2)/(x1-x2);
    if(sgn(a) >= 0) return 0;
    double b = y2/x2-a*x2;
    int cnt = 0;
    FOR(i,0,n-1) if(!sgn(a*x[i]*x[i]+b*x[i]-y[i])) cnt |= (1<<i);
    return cnt;
}

inline void Solve(){
    scanf("%d%*d",&n);
    FOR(i,0,n-1) scanf("%lf%lf",x+i,y+i);
    FOR(i,0,n-1){
        FOR(j,i+1,n-1){
            w[i][j] = calc(x[i],y[i],x[j],y[j]);
        }
    }
    f[0] = 0;
    FOR(S,1,(1<<n)) f[S] = 1e9;
    FOR(S,0,(1<<n)-1){
        FOR(i,0,n-1){
//            if((1<<i)&S) continue;
            FOR(j,i+1,n-1){
//                if((1<<j)&S) continue;
                f[S|w[i][j]] = std::min(f[S|w[i][j]],f[S]+1);
            }
        }
        FOR(i,0,n-1){
//            if((1<<i)&S) continue;
            f[S|(1<<i)] = std::min(f[S|(1<<i)],f[S]+1);
        }
    }
    printf("%d\n",f[(1<<n)-1]);
 //   clear();
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 200+5;
int N,M,P;
int a[MAXN][MAXN],suml[MAXN][MAXN],sum1[MAXN][MAXN],sum2[MAXN][MAXN];

int l[MAXN],r[MAXN],u[MAXN],d[MAXN];
//  left    right   up      down

inline void Solve(){
    FOR(i,0,MAXN-1) l[i] = r[i] = u[i] = d[i] = INT_MIN;
    FOR(i,1,N) FOR(j,1,M) scanf("%d",&a[i][j]),sum1[i][j] = sum2[i][j] = a[i][j];
    FOR(i,1,N) FOR(j,1,M) sum1[i][j] += sum1[i][j-1],sum2[i][j] += sum2[i-1][j];
    FOR(i,1,N){
        FOR(j,i,N){
            int t = INT_MIN,tt = INT_MIN;
            FOR(k,1,M){
                tt = std::max(0,tt) + sum2[std::max(i,j)][k] - sum2[std::min(i,j)-1][k];
                // DEBUG(tt);
                t = std::max(t,tt);
            }
            FOR(k,j,N) u[k] = std::max(u[k],t);
            FOR(k,1,i) d[k] = std::max(d[k],t);
        }
    }
    FOR(i,1,M){
        FOR(j,i,M){
            int t = INT_MIN,tt = INT_MIN;
            FOR(k,1,N){
                tt = std::max(0,tt) + sum1[k][std::max(i,j)] - sum1[k][std::min(i,j)-1];
                t = std::max(t,tt);
            }
            FOR(k,j,M) l[k] = std::max(l[k],t);
            FOR(k,1,i) r[k] = std::max(r[k],t);
        }
    }
    // FOR(i,1,N) printf("%d ",u[i]);puts("");
    // FOR(i,1,N) printf("%d ",d[i]);puts("");
    // FOR(i,1,M) printf("%d ",l[i]);puts("");
    // FOR(i,1,M) printf("%d ",r[i]);puts("");
    int ans = u[N];
    FOR(i,1,N){
        FOR(j,1,M){
            if(a[i][j] <= P) continue;
            int t = std::max(u[i-1],d[i+1]);
            t = std::max(t,std::max(l[j-1],r[j+1]));
            t = std::max(t,u[N]-a[i][j]+P);
            ans = std::min(ans,t);
        }
    }
    printf("%d\n",ans);
}

int main(){
    while(~scanf("%d%d%d",&N,&M,&P)) Solve();
    return 0;
}
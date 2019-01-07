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
#define int LL
const int MAXN = 1000+5;
int N,M;
int a[MAXN];
std::map<int,bool> S;
bool f[MAXN][MAXN];
int ff[MAXN];

inline void Solve(){
    scanf("%lld%lld",&N,&M);S.clear();
    FOR(i,1,N) scanf("%lld",a+i);
    FOR(i,1,M){
        int x;scanf("%lld",&x);
        S[x] = true;
    }
    CLR(f,false);
    FOR(i,1,N) f[i+1][i] = true;
    FOR(i,2,N) f[i-1][i] = S[a[i]-a[i-1]];
    FOR(i,3,N) f[i-2][i] = ((a[i]-a[i-1] == a[i-1]-a[i-2]) && (S[a[i-1]-a[i-2]]));
    FOR(j,4,N){
        ROF(i,j-3,1){
            FOR(k,i+1,j) f[i][j] |= (f[i][k]&f[k+1][j]);
            if(S[a[j]-a[i]]) f[i][j] |= f[i+1][j-1];
            FOR(k,i+1,j){
                if(a[j] - a[k] == a[k] - a[i] && S[a[j]-a[k]]){
                    f[i][j] |= (f[i+1][k-1] & f[k+1][j-1]);
                }
            }
        }
    }
    CLR(ff,0);
    FOR(j,2,N){
        if(f[1][j]){ff[j] = j;continue;}
        ff[j] = ff[j-1];
        FOR(i,1,j) if(f[i][j]) ff[j] = std::max(ff[j],ff[i-1]+(j-i+1));
    }
    printf("%lld\n",ff[N]);
}

signed main(){
    int T;scanf("%lld",&T);
    while(T--) Solve();
    return 0;
}
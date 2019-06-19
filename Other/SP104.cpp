#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
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

const int MAXN = 2000+5;

int n,m;
LL a[MAXN][MAXN];

LL det(){
    LL ret = 1;
    FOR(i,1,n-1){
        FOR(j,i+1,n-1){
            while(a[j][i]){
                LL t = a[i][i]/a[j][i];
                FOR(k,i,n-1) a[i][k] -=  a[j][k]*t;
                FOR(k,i,n-1) std::swap(a[i][k],a[j][k]);
                ret *= -1;
            }
        }
        ret *= a[i][i];
    }
    return ret;
}

inline void Solve(){
    CLR(a,0);
    scanf("%d%d",&n,&m);
    FOR(i,1,m){
        int u,v;scanf("%d%d",&u,&v);--u;--v;
        a[u][v] = a[v][u] = -1;
        a[u][u]++;a[v][v]++;
    }
    printf("%lld\n",det());
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

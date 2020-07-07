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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
int n;
int ans[MAXN][MAXN];

inline void printans(){
    FOR(i,1,n) FOR(j,1,n) printf("%d%c",ans[i][j]," \n"[j==n]);
}

inline void Solve(){
    scanf("%d",&n);
    if(n&1) FOR(i,1,n) FOR(j,1,n) printf("%d%c",(i-1)*n+j," \n"[j==n]);
    else FOR(i,1,n) FOR(j,1,n) printf("%d%c",(i&1) ? ((i-1)*n+j) : ((i-1)*n+n-j+1)," \n"[j==n]);
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

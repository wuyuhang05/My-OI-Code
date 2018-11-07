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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000+5;
int a[MAXN],N;
int lsum[MAXN],rsum[MAXN];

inline void Solve(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i);
    CLR(lsum,0);CLR(rsum,0);
    FOR(i,1,N) lsum[i] = lsum[i-1]+a[i];
    ROF(i,N,1) rsum[i] = rsum[i+1] + a[i];
    FOR(i,1,N) a[i] = lsum[i]-rsum[i];
    if(N & 1){
        int mid = (N+1)/2;
        int d = std::min(a[mid],std::max(a[mid+1],a[mid-1]));
        puts(d == 0 ? "tie" : (d > 0 ? "win" : "lose"));
    }
    else{
        int mid = (N+1)/2;
        int d = std::max(a[mid],a[mid+1]);
        puts(d == 0 ? "tie" : (d > 0 ? "win" : "lose"));
    }
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

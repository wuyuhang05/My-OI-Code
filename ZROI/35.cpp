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
int T;
inline void Solve(){
    int N,ans=INT_MAX;scanf("%d",&N);
    int q = std::sqrt((double)N);
    FOR(i,1,q){
        if(N % i) continue;
        //DEBUG(i);DEBUG(N/i);
        ans = std::min(ans,i*2+(N/i)*2);
    }
    printf("%d\n",ans);
}

int main(){
    scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
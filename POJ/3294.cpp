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

const int MAXN = 100+5;
const int MAXM = 1000+5;
char s[MAXN][MAXM];
int N;
std::map<U LL,int> S;

inline bool check(int k){
    FOR()
}

inline void Solve(){
    scanf("%d",&N);
    if(!N) {puts("?");return 0;}
    FOR(i,1,N) scanf("%s",s[i]+1);
    int L = (N+1)/2,R = N,ans = 0;
    while(L <= R){
        int mid = (L+R) >> 1;
        if(check(mid)) L = mid+1,ans = mid;
        else R = mid-1;
    }
    if(ans) printf("%d\n",ans);
    else puts("?");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}
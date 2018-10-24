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

const int MAXN = 100000 + 5;
int a[MAXN],N;
int ans;

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i);
    std::sort(a + 1,a + N + 1);
    int k = N/2+1,l=1;
    int ans = INT_MAX;
    FOR(i,k,N){
        ans = std::min(ans,a[i]-a[l++]);
    }
    printf("%d\n",ans);
    return 0;
}
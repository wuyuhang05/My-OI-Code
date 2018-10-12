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

const int MAXN = 300000 + 5;
int N;
int a[MAXN];
int ans = 0;

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a + i);
    std::sort(a + 1,a + N + 1);
    int max = 0;
    ROF(i,N,1){
        if(a[i]+N >= max) ans++;
        max = std::max(max,a[i] + (N-i+1));
    }
    printf("%d\n",ans);
    return 0;
}
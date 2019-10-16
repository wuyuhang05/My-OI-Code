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
int N,a[MAXN],cnt[MAXN];

int main(){
    scanf("%d",&N);
    FOR(i,1,N) scanf("%d",a+i),cnt[a[i]]++;
    std::sort(a+1,a+N+1);
    if(a[N-1] != a[N]) {puts("Impossible");return 0;}
    cnt[a[N]] -= 2;
    FOR(i,1,a[N]-1){
        int d = std::max(i,a[N]-i);
        if(!cnt[d]){
            puts("Impossible");return 0;
        }
        cnt[d]--;
    }
    FOR(i,1,(a[N]+1)/2){
        if(cnt[i]){
            puts("Impossible");return 0;
        }
    }
    puts("Possible");
    return 0;
}
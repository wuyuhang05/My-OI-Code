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

#define R register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(R int i = a;i <= b;++i)
#define RFOR(i,a,b) for(R int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int BASE = 31;
const int MAXN = 1000000 + 5;
char str[MAXN],stack[MAXN];
int N,top;
U LL hash[MAXN],a[MAXN];

int main(){
    freopen("str.in","r",stdin);
    freopen("str.out","w",stdout);
    scanf("%s",str+1);
    N = strlen(str+1);
    FOR(i,1,N){
        if(top && stack[top] == str[i])
            --top;
        else{
            stack[++top] = str[i];
            hash[top] = hash[top-1] * BASE + str[i];
        }
        a[i] = hash[top];
    }
    std::sort(a,a + N + 1);
    LL cnt = 0,ans = 0;
    FOR(i,0,N){
        if(!i || a[i] != a[i-1]) cnt = 1;
        else
            ans += cnt++;
    }
    printf("%lld\n",ans);
    return 0;
}

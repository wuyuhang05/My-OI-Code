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

const int MAXN = 3000005;
int inv[MAXN];
int N,P;

int main(){
    scanf("%d%d",&N,&P);
    inv[1] = 1;
    puts("1");
    FOR(i,2,N)
        printf("%d\n",inv[i] = (LL)(P-P/i)*inv[P%i]%P);
    return 0;
}

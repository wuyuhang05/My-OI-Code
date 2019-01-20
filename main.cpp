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

const int MAXN = 100000+5;
int N,a[MAXN];
double x;

int main(){
    scanf("%d%lf",&N,&x);
    FOR(i,1,N) scanf("%d",a+i);
    std::sort(a+1,a+N+1);
    int i = 1;
    while(i <= N){
        while(a[i] <= x && i <= N) i++;
        if(i > N) break;
        x = (x+1.0*a[i])*0.5;i++;
    }
    printf("%.3f\n",x);
    return 0;
}
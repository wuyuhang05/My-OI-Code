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
double x[MAXN],y[MAXN];
int N;

bool cmp(double x,double y){
    return x > y;
}

double ans;

inline double get(double a[],double b[]){ // suma < sumb
    double suma=0.0,sumb=0.0,ans=0.0;
    int i=1,j=1;
    while(i <= N){
        suma += a[i];
        while(j <= N && suma > sumb) sumb += b[j++];
        if(suma <= sumb) ans = std::max(ans,suma-i-j+1);
        // DEBUG(suma);DEBUG(sumb);DEBUG(i);DEBUG(j);
        i++;
    }
    return ans;
}

int main(){
    freopen("coin.in","r",stdin);
    freopen("coin.out","w",stdout);
    scanf("%d",&N);
    FOR(i,1,N) scanf("%lf%lf",x+i,y+i);
    std::sort(x+1,x+N+1,cmp);std::sort(y+1,y+N+1,cmp);
    printf("%.4f",std::max(get(x,y),get(y,x)));
    return 0;
}
/*
4
1.4 3.7
1.2 2
1.6 1.4
1.9 1.5
*/
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

int N;
double x;
double dist = INT_MAX*1.0;

int main(){
    scanf("%d%lf",&N,&x);
    int up,down;
    FOR(i,1,N){
        int L = 1,R = N;
        while(L < R){
            int mid = (L + R) >> 1;
            double ret = (double)i/(double)mid;
            if(ret <= x) R = mid;
            else L = mid+1;
        }
        if(R <= N && std::fabs((double)i/(double)R - x) < dist){
            dist = std::fabs((double)i/(double)R - x);                
            up = i;down = R;
        }
        if(R >= 2 && std::fabs((double)i/(double)(R-1)-x) < dist){
            dist = std::fabs((double)i/(R-1)-x);
            up = i;down = R-1;
        }
    }
    printf("%d\n%d\n",up,down);
    return 0;
}
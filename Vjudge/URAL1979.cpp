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
int n,sum;

int main(){
    scanf("%d",&n);
    FOR(i,0,n-1){
        FOR(j,0,n-1){
            printf("%d ",n*i+j+1);
        }
        puts("");
    }
    FOR(i,0,n-1){
        FOR(j,0,(n<<1)-1){
            printf("%d ",n*n+(n<<1)*i+j+1);
        }
        FOR(j,0,n-1){
            printf("%d ",5*n*n-((i<<1)+1)*n+j+1);
        }
        FOR(j,0,n-1){
            printf("%d ",5*n*n-((i<<1)+2)*n+j+1);
        }
        puts("");
    }
    FOR(i,0,n-1){
        FOR(j,0,n-1){
            printf("%d ",5*n*n+(i+1)*n-j);
        }
        puts("");
    }
    return 0;
}
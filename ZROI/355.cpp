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

LL dist(int x1,int y1,int x2,int y2){
    return std::abs(x1-x2) + std::abs(y1-y2);
}

int main(){
    int x1,y1,x2,y2;
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    if(x1 == 1 && x2 == 1 || x1 == 19 && x2 == 19){
        printf("%d\n",std::abs(y1-y2));return 0;
    }
    if(y1 == 1 && y2 == 1 || y1 == 19 && y2 == 19){
        printf("%d\n",std::abs(x1-x2));return 0;
    }
    LL ans = dist(x1,y1,1,1) + dist(x2,y2,1,1);
    FOR(i,0,1){
        FOR(j,0,1){
            ans = std::min(ans,dist(x1,y1,18*i+1,18*j+1) + dist(x2,y2,18*i+1,18*j+1));
        }
    }
    printf("%lld\n",ans);
    return 0;
}
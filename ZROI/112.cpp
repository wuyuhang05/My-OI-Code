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

int x,y,s,t;
int main(){
    scanf("%d%d%d%d",&x,&y,&s,&t);
    if(s < 0) s = -s,x = -x;
    if(t < 0) t = -t,y = -y;
    if(x == 1 && y == x){
        printf("%d\n",s+t);
        return 0;
    }
    if(x == 1 && y == 0){
        if(s <= t){
            printf("%d\n",t);
            return 0;
        }
        printf("%d\n",(t%2 == s%2) ? s : s + 1);
        return 0;
    }
    if(x == 0 && y == 1){
        if(t <= s){
            printf("%d\n",s);
            return 0;
        }
        printf("%d\n",(t%2 == s%2) ? t : t + 1);
        return 0;
    }
    printf("%d\n",std::max(s,t));
    return 0;
}
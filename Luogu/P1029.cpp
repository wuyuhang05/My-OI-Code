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

int x,y;
int ans = 0;

int gcd(int x,int y){
    if(!y) return x;
    return gcd(y,x%y);
}

int main(){
    scanf("%d%d",&x,&y);
    int q = std::sqrt(x*y);
    FOR(i,1,q){
        if(!((x*y)%i) && gcd(i,(x*y)/i) == x) ans++;
    }
    printf("%d\n",ans*2);
    return 0;
}

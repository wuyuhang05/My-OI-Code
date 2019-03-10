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

#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
int n,a[MAXN],ans,t;

inline bool cmp(int x,int y){
    return x > y;
}

int main(){
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d",a+i);
    std::sort(a+1,a+n+1,cmp);
    for(;a[t]>=t;t++);t--;
    if(!((a[t]-t)%2)){
        int j = 0;
        for(;a[t+j]>=t;j++);
        if(j & 1){
            puts("Second");return 0;
        }
    }
    puts("First");
    return 0;
}
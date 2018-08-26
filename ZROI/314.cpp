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

#define LL long long
#define U unsigned
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define RFOR(i,a,b) for(int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
    int N;
    int now = 1,len = 0,ans = 0;
    scanf("%d",&N);
    if(N == 1){
        puts("6");
        return 0;
    }
    N -= now;len++;
    ans = 7;now += 6;
    while(N > now){
         N -= now;
        ans+=6;
        len++;
        now += 6;
    }
    FOR(i,1,4){
        if(N > len){
            N -= len;
            ans++;
        }
    }
    if(N > len+1){
        N -= (len+1);
        ans++;
    }
    printf("%d\n",++ans);
    return 0;
}

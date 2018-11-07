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

const int MAXL = 500+5;
char str[MAXL];

inline void Solve(){
    int cnt = 0;
    FOR(j,1,2){
        FOR(i,1,6){
            scanf("%s",str+1);
            if(j == 2 && str[2]=='J') cnt++;
        }
    }
    FOR(i,1,42) scanf("%*s");
    scanf("%*s");
    if(cnt == 2) puts("First");
    else puts("Second");
}

int main(){
    int T;scanf("%d",&T);
    while(T--) Solve();
    return 0;
}

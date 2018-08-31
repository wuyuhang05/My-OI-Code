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

const int MAXN = 100 + 5;

int vis[MAXN];
int N,M;

inline void pls(int &x){
    x++;
    if(x == N + 1) x = 1;
}

int main(){
    scanf("%d%d",&N,&M);
    CLR(vis,0);
    int s = 0;
    FOR(i,1,N){
        FOR(j,1,M){
            pls(s);
            if(vis[s]) j--;
        }
        printf("%d%c",s,(i == N) ? '\n' : ' ');
        vis[s] = true;
    }
    return 0;
}

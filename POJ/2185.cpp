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
#define int LL
const int MAXN = 10000+5;
const int MAXM = 75+5;
char a[MAXN][MAXM];
char str[MAXN];
int next[MAXN];
int N,M;

inline int get(char *str){
    int len = strlen(str);CLR(next,0);
    next[0] = -1;int i = 0,j = -1;
    while(i < len){
        if(j == -1 || str[i] == str[j]) i++,j++,next[i] = j;
        else j = next[j];
    }
    return i-next[i];
}

inline int gcd(int x,int y){
    return !y ? x : gcd(y,x%y);
}

inline int lcm(int x,int y){
    return (1ll*x*y)/gcd(x,y);
}

signed main(){
    scanf("%lld%lld",&N,&M);
    FOR(i,1,N) scanf("%s",a[i]);
    int x=1,y=1;
    FOR(i,1,N) x = lcm(x,get(a[i]));
    FOR(i,1,M){
        FOR(j,1,N) str[j-1] = a[j][i];
        y = lcm(y,get(str));
    }
    x = std::min(x,M);y = std::min(y,N);
    printf("%lld\n",1ll*x*y);
    return 0;
}
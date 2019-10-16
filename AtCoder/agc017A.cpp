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

int N,P;
int p[2];

int main(){
    scanf("%d%d",&N,&P);
    FOR(i,1,N){
        int x;scanf("%d",&x);
        p[x%2]++;
    }
    LL num = 0;
    if(p[1]) num = (1ll<<(p[1]-1))*(1ll<<p[0]);
    if(P){
        printf("%lld\n",num);
    }
    else printf("%lld\n",(1ll<<N)-num);
    return 0;
}

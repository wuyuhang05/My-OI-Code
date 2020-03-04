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
//#define int LL
const int MAXN = 50+5;
LL a[MAXN],b[MAXN*100],n,base=62;

inline void Gauss(){
    FOR(i,1,n){
        LL x = a[i];
        ROF(j,base,0){
            if((x>>j)&1){
                if(b[j]) x ^= b[j];
                else {b[j] = x;break;}
            }
        }
    }
}
LL ans = 0;
int main(){
    scanf("%lld",&n);
    FOR(i,1,n) scanf("%lld",a+i);
    Gauss();
    ROF(i,base,0) ans = std::max(ans,ans^b[i]);
    printf("%lld\n",ans);
    return 0;
}
/*
*/
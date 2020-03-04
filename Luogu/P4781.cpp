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

#define fi first
#define lc (x<<1)
#define se second
#define U unsigned
#define rc (x<<1|1)
#define Re register
#define LL long long
#define MP std::make_pair
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;

const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
    int res = 1;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int n,k,x[MAXN],y[MAXN],ans;

int main(){
    scanf("%d%d",&n,&k);
    FOR(i,1,n) scanf("%d%d",x+i,y+i);
    FOR(i,1,n){
        int s1 = 1,s2 = 1;
        FOR(j,1,n){
            if(j == i) continue;
            s1 = 1ll*s1*((1ll*k-x[j]+ha)%ha)%ha;s2 = 1ll*s2*((1ll*x[i]-x[j]+ha)%ha)%ha;
        }
        s2 = qpow(s2);s1 = 1ll*s1*s2%ha*y[i]%ha;
        ans = (ans+s1)%ha;
    }
    printf("%d\n",ans);
    return 0;
}
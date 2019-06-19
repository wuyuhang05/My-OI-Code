#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1000+5;
int n,m;
std::map<std::string,int> S;
std::string str[MAXN];

inline LL qpow(LL a,LL n,LL ha){
    LL res = 1ll;
    while(n){
        if(n & 1) res = 1ll*res*a%ha;
        a = 1ll*a*a%ha;
        n >>= 1;
    }
    return res;
}

int main(){
    int T;scanf("%d",&T);
    while(T--){
        LL n,q,ha;scanf("%lld%lld%lld",&n,&q,&ha);
        LL sum = 0;
        sum = (qpow(q,n+1,ha)%ha-1+ha)%ha*qpow(q-1,ha-2,ha)%ha;
        sum--;if(sum < 0) sum += ha;
        printf("%lld\n",sum);
    }
    return 0;
}

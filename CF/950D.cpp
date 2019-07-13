#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
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

LL n,q,x,N;

inline LL calc(LL x,LL len,int gg){
    if((x&1) == gg) return x/2 + gg;
    LL pos = x/2+(gg^1);
    return calc(pos,(len+(gg^1))/2,gg^(len&1))+(len+gg)/2;
}

inline void Solve(){
    scanf("%lld",&x);
    printf("%lld\n",calc(x,n,1));
}

int main(){
    scanf("%lld%lld",&n,&q);
    while(q--) Solve();
    return 0;
}

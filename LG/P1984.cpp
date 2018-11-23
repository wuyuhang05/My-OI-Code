#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
int n,m,l,r;
long long Max,Diff,st,ed;
unsigned long long Seed;

template <class Tp> Tp Rand(Tp MOD) {
    Seed*=999999999;
    Seed^=2003112020040612ULL;
    Seed>>=13;
    Seed<<=7;
    return Tp(Seed%MOD)+1;
}

void generate() {
    l=Rand(n-1),r=l+Rand(n-l),st=Rand(Max),ed=st+1LL*(r-l)*(Rand(Diff+1)-1);
}

const int MAXN = 10000000+5;
const int ha = 1000000000+7;
int cf[MAXN];

signed main() {
    scanf("%lld%lld%llu%lld%lld",&n,&m,&Seed,&Max,&Diff);
    for(int i=1;i<=m;++i) {
        generate();
        LL d = ((ed-st)/(r-l))%ha;
		ed %= ha;st %= ha;
		cf[l] = (cf[l]+st)%ha;
		cf[l+1] = (cf[l+1]+(d-st+ha)%ha)%ha;
		cf[r+1] = (cf[r+1]+(-ed-d+ha)%ha)%ha;
		cf[r+2] = (cf[r+2] + ed)%ha;
    }
	FOR(i,1,n) cf[i] = (cf[i-1]+cf[i])%ha;
	FOR(i,1,n) cf[i] = (cf[i-1]+cf[i])%ha;
	int ans1=0,ans2=LLONG_MIN;
	FOR(i,1,n){
		ans1 ^= cf[i];ans2 = std::max(ans2,cf[i]);
	}
	printf("%lld %lld\n",ans1,ans2);
    return 0;
}
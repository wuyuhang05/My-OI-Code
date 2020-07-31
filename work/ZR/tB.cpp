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
#define db double
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2e5 + 5;
const int ha = 998244353;
int fac[MAXN],inv[MAXN],n;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void add(int &x,int y){
    x += y;if(x >= ha) x -= ha;
}

int a[MAXN],b[MAXN];LL s[MAXN];

inline int C(int n,int m){
    if(n < m) return 0;
    if(n < 0) return 0;
    if(m < 0) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    scanf("%d",&n);
    FOR(i,1,n) scanf("%d%d",a+i,b+i),b[i] += a[i];
    ROF(i,n,1) s[i] = s[i+1]+b[i];
    int now = 1;
    FOR(i,1,n) now = 1ll*now*C(s[i],a[i])%ha;
    int sma = 0;FOR(i,1,n) sma += a[i];
    FOR(k,0,n-1){
        printf("%lld ",1ll*now*C(s[1]-k*n,sma)%ha);
    }
    puts("");
    return 0;
}


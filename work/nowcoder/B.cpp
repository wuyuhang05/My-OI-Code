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

#define int LL
const int MAXN = 2000+5;
int n,m,k,ha;
int a[MAXN];

inline int mul(int a,int b,int m){
    int c = a*b-(LL)((long double)a*b/m+0.5)*m;
    return c < 0 ? c+m : c;  //就是算的a*b%m;
}

inline int get(int x){
    int e = 0;
    while(x != 1) x /= k,e++;
    return e;
}

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = mul(res,a,ha);
		a = mul(a,a,ha);
		n >>= 1;
	}
	return res;
}

signed main(){
    scanf("%lld%lld%lld%lld",&n,&m,&k,&ha);
    if(k == 1){
        printf("%lld\n",1%ha);
        return 0;
    }
    FOR(i,1,n){
        FOR(j,1,m){
            int x;scanf("%lld",&x);
            a[i] += get(x);
        }
    }
    std::sort(a+1,a+n+1);
    printf("%lld\n",qpow(k,a[n]));
    return 0;
}

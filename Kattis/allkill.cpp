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
int n,t;
int a[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

int main(){
    scanf("%d%d",&n,&t);int tt = t;
    FOR(i,1,n) scanf("%d",a+i),tt -= a[i];
    if(tt < 0){
        puts("0");
        return 0;
    }
    int ans = tt+1;
    int now = tt+1+n;
    FOR(i,1,n){
        if(i > 1) ans = 1ll*ans*now%ha;
        (now += a[i]) %= ha;
        (now += ha-1) %= ha;
    }
    printf("%d\n",ans);
    return 0;
}

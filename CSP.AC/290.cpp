#include <bits/stdc++.h>

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

const int ha = 998244353;
const int inv2 = 499122177;

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
    int n,x,y;scanf("%d%d%d",&n,&x,&y);
    int p = 1ll*x*qpow(y)%ha;
    int ans = 1ll*n*(n-1)%ha*inv2%ha;
    int t = (1+ha-p)%ha;t = 1ll*t*t%ha;
    t = (1+ha-t)%ha;t = qpow(t);
    ans = 1ll*ans*t%ha;
    ans = 1ll*ans*(1+ha-p)%ha;
    ans = 1ll*ans*p%ha;
    printf("%d\n",ans);
    return 0;
}

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

int q,a,b,ha;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline int gcd(int a,int b){
    if(a < b) return gcd(b,a);
    if(!b) return (qpow(q,a)+ha-1)%ha;
    return gcd(b,a%b);
}

int main(){
    int T;scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&q,&a,&b,&ha);
        LL x = qpow(q,a)-1,y = qpow(q,b)-1;
        printf("%d\n",gcd(a,b));
    }
    return 0;
}
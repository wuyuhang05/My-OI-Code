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
const int inv = 499122177;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct Node{// x+sqrt(5)y
	int x,y;
	Node(int x=0,int y=0) : x(x),y(y) {}
	
	inline Node operator + (const Node &t) const {
		return Node((x+t.x)%ha,(y+t.y)%ha);
	}
	
	inline Node operator - (const Node &t) const {
		return Node((x+ha-t.x)%ha,(y+ha-t.y)%ha);
	}
	
	inline Node operator * (const Node &t) const {
		return Node((1ll*x*t.x%ha+5ll*y%ha*t.y%ha)%ha,(1ll*x*t.y%ha+1ll*y*t.x%ha)%ha);
	}
	
	inline Node inv(){
		int inv = (1ll*x*x%ha+ha-5ll*y%ha*y%ha)%ha;
		inv = qpow(inv);
		return Node(1ll*x*inv%ha,ha-1ll*y*inv%ha);
	}
}a,b;

inline Node qpow(Node a,LL n){
	Node res(1,0);
	while(n){
		if(n & 1) res = res*a;
		a = a*a;
		n >>= 1;
	}
	return res;
}

int main(){
	LL n;scanf("%lld",&n);++n;
	a = Node(inv,inv);b = Node(inv,ha-inv);
	a = qpow(a,n);b = qpow(b,n);
	a = a-b;
	Node c(0,1);
	a = a*c.inv();
	printf("%d\n",a.x);
	return 0;
}
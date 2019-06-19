#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define Re register
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

// f(n) = 2f(n-2)+f(n-1)+1
const int ha = 998244353;

struct Matrix{
	static const int MAXN = 3;
	LL a[3][3];
	
	inline void clear(){
		CLR(a,0);
	}
	
	inline void pre(){
		FOR(i,0,2) a[i][i] = 1;
	}
	
	friend Matrix operator * (const Matrix &x,const Matrix &y){
		Matrix res;res.clear();
		FOR(i,0,2){
			FOR(j,0,2){
				LL t = 0;
				FOR(k,0,2){
					(t += x.a[i][k]*y.a[k][j]%ha) %= ha;
				}
				res.a[i][j] = t;
			}
		}
		return res;
	}
	
	Matrix operator ^ (LL n) const {
		Matrix res,a = (*this);res.clear();
		FOR(i,0,2) res.a[i][i] = 1;
		while(n){
			if(n & 1) res = res*a;
			a = a*a;
			n >>= 1;
		}
		return res;
	}
}x;

int main(){
	//freopen("X.in","r",stdin);
	//freopen("X.out","w",stdout);
	x.clear();
	x.a[0][0] = 1;x.a[0][1] = 2;x.a[0][2] = 1;
	x.a[1][0] = 1;x.a[2][2] = 1;
	LL n;scanf("%lld",&n);
	if(n == 1){
		puts("1");return 0;
	}
	if(n == 2){
		puts("2");return 0;
	}
	n--;n--;
	Matrix res = x ^ n;
	LL ans = (2ll*res.a[0][0]+res.a[0][1]+res.a[0][2])%ha;
	printf("%d\n",ans);
	return 0;
}

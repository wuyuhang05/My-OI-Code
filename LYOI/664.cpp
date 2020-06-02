#include<bits/stdc++.h>

#define fi first
#define se second
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

const int MNAX = 2e5 + 5;

struct Complex{
	int x,y;
	Complex(int x=0,int y=0) : x(x),y(y) {}
	friend Complex operator + (const Complex &x,const Complex &y){
		return Complex(x.x+y.x,x.y+y.y);
	}
	friend Complex operator - (const Complex &x,const Complex &y){
		return Complex(x.x-y.x,x.y-y.y);
	}
	friend Complex operator * (const Complex &x,const Complex &y){
		return Complex()
		// w^2=-w-1
	}
}

int main(){
	return 0;
}
/*
f[i][S] %k=i 三进制状态是 S
f[i][S]+f[j][T] -> f[(i+j)%k][S+T]
*/
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

int n;
std::map<std::string,int> S;

int main(){
	std::ios::sync_with_stdio(false);
	std::cin >> n;
	FOR(i,1,2*n-1){
		std::string t;std::cin >> t;
		S[t] ^= 1;
	}
	for(auto x:S){
		if(x.se){
			std::cout << x.fi << '\n';
			return 0;
		}
	}
	return 0;
}
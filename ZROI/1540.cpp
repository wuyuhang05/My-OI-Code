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

const int MAXN = 3e5 + 5;
std::string s[MAXN];

inline bool cmp(std::string a,std::string b){
	return a+b < b+a;
}

int main(){
	std::ios::sync_with_stdio(false);
	int n;std::cin >> n;
	FOR(i,1,n) std::cin >> s[i];
	std::sort(s+1,s+n+1,cmp);
	FOR(i,1,n) std::cout << s[i];
	std::cout << '\n';
	return 0;
}
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

const int MAXN = 20+1;

class EllysCandies{
	int n;
	int a[MAXN];
	int f[(1<<MAXN)+2];
	
	inline int dfs(int S){
		if(f[S] != -1e9) return f[S];
		int now = 0;
		FOR(i,0,n-1) if((S>>i)&1) now += a[i];
		int &ans = f[S];
		FOR(i,0,n-1){
			if((S>>i)&1) continue;
			ans = std::max(ans,a[i]+now-dfs(S|(1<<i)));
		}
		return ans;
	}
	
	public:
		
	inline std::string getWinner(std::vector<int> cases){
		n = cases.size();
		if(n & 1){
			return "Elly";
		}
		else{
			return "Kris";
		}
		FOR(i,0,n-1) a[i] = cases[i];
		FOR(i,0,(1<<n)) f[i] = -1e9;
		f[(1<<n)-1] = 0;
		int t = dfs(0);
//		DEBUG(f[0]);DEBUG(f[1]);DEBUG(f[2]);DEBUG(f[3]);
		if(t > 0) return "Elly";
		else if(t < 0) return "Kris";
		else return "Draw";
	}
};
#ifdef RainAir
EllysCandies test;

int main(){
	std::vector<int> S;
	FOR(i,1,20) S.pb(1000);
	std::cout << test.getWinner({1000,1000,2,1}) << std::endl;
//	std::cout << test.getWinner({42, 13, 17, 666, 55, 100, 3, 20, 81, 42, 123}) << std::endl;
	return 0;
}
#endif

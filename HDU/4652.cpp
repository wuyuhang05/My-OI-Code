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

inline double qpow(double a,int n){
	if(n == -1) return 1/a;
	double res = 1;
	while(n){
		if(n & 1) res = res*a;
		a = a*a;
		n >>= 1;
	}
	return res;
}

int main(){
	int T;
	while(~scanf("%d",&T)){
		while(T--){
			int opt,n,m;scanf("%d%d%d",&opt,&m,&n);
			if(opt == 0){
				printf("%.10f\n",1.0*(qpow(m,n)-1)/(m-1));
			}
			else{
				double ans=0,t = 1;
				FOR(i,1,n){
					ans += t;
					t = t*m/(m-i);
				}
				printf("%.10f\n",ans);
			}
		}
	}
	return 0;
}
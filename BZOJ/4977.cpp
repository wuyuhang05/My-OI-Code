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
#define int LL
const int MAXN = 5e5 + 5;

P a[MAXN];
int n,m,N;
std::priority_queue<int> q;

signed main(){
	scanf("%lld%lld",&n,&m);N = n+m;
	FOR(i,1,n) scanf("%lld",&a[i].fi),a[i].se = -1e9;
	FOR(i,1,m) scanf("%lld%lld",&a[i+n].fi,&a[i+n].se);
	std::sort(a+1,a+N+1);
	int ans = 0;
	FOR(i,1,N){
		if(a[i].se == -1e9){
			if(q.empty() || q.top()+a[i].fi <= 0) continue;
			ans += q.top()+a[i].fi;q.pop();
			q.push(-a[i].fi);
		}
		else q.push(-a[i].fi+a[i].se);
	}
	printf("%lld\n",ans);
	return 0;
}
/*
3 3
4 4 4
2 3
1 3
5 3
*/
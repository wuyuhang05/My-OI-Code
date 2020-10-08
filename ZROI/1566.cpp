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

const int MAXN = 1e5 + 5;
int n,k,a[MAXN];
int ans[MAXN];
P lim[MAXN];
int vis[MAXN];
int tmp[MAXN];

inline void work(int n,int col){
	if(n <= 0) return;
	std::set<int> S;
	FOR(i,1,n){
		lim[i] = MP(0,0);
		auto p = S.lower_bound(a[i]);
		if(p != S.end()) lim[i].fi = *p;
		if(p != S.begin()) --p,lim[i].se = *p;
		S.insert(a[i]);
	}
	FOR(i,1,n) vis[a[i]] = 0;
	ROF(i,n,1){
		if(vis[a[i]]) continue;
		vis[a[i]] = 1;ans[a[i]] = col;
		vis[lim[i].fi] = vis[lim[i].se] = -1;
	}
	int tp = 0;
	FOR(i,1,n) if(vis[a[i]] == -1) tmp[++tp] = a[i];
	FOR(i,1,tp) a[i] = tmp[i];
	work(tp,col+1);
}

int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",a+i);
	work(n,1);
	FOR(i,1,n) printf("%d ",ans[i]);puts("");
	return 0;
}
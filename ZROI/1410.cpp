#include<bits/stdc++.h>
#include "sorting.h"

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

const int MAXN = 1e6 + 5;
int n;
int p[MAXN],t[MAXN];

P a[MAXN];
int vis[MAXN];
std::vector<int> G[MAXN];

inline void label(bool flag=0){
	FOR(i,0,n) vis[i] = 0;
	FOR(i,1,n){
		if(!vis[i]){
			int x = i;vis[x] = ++vis[0];
			if(flag) G[vis[0]].pb(x);
			while(!vis[t[x]]){
				vis[t[x]] = vis[0],x = t[x];
				if(flag) G[vis[0]].pb(x);
			}
		}
	}
}

inline bool chk(int k){
	FOR(i,1,n) t[i] = p[i];
	FOR(i,1,k) std::swap(t[a[i].fi],t[a[i].se]);
	label();
	return n-vis[0] <= k;
}

std::vector<P> ans;
int to[MAXN],f[MAXN];

inline int findSwapPairs(int N,int S[],int M,int X[],int Y[],int P[],int Q[]){
	n = N;
	FOR(i,1,n) p[i] = S[i-1];
	bool flag = 1;
	FOR(i,1,n) flag &= (p[i]==i);
	if(flag){
		puts("0");return 0;
	}
	int m;m = M;
	FOR(i,1,m) a[i] = MP(X[i-1]+1,Y[i-1]+1);
	int l = 1,r = m,res = -1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(chk(mid)) res = mid,r = mid-1;
		else l = mid+1;
	}
	printf("%d\n",res);
	FOR(i,1,n) t[i] = p[i];
	FOR(i,1,res) std::swap(t[a[i].fi],t[a[i].se]);
	label(1);
	FOR(i,1,vis[0]){
		for(int j = 1;j < G[i].size();++j){
			ans.pb(MP(G[i][0],G[i][j]));
		}
	}
	while(ans.size() != res) ans.pb(MP(1,1));
	FOR(i,1,n) to[i] = f[i] = i;
	ROF(i,res,1){
		std::swap(to[f[a[i].fi]],to[f[a[i].se]]);
		std::swap(f[a[i].fi],f[a[i].se]);
		ans[i-1].fi = to[ans[i-1].fi];
		ans[i-1].se = to[ans[i-1].se];
	}
	// FOR(i,0,(int)ans.size()-1) printf("%d %d\n",ans[i].fi-1,ans[i].se-1);
	FOR(i,0,(int)ans.size()-1) P[i] = ans[i].fi-1,Q[i] = ans[i].se-1;
	return res;
}

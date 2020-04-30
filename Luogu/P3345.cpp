
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
const int MAXN = 1e5 + 5;
const int MAXM = 17;

std::vector<P> G[MAXN],T[MAXN];
int RT;
int f[MAXN][MAXM+1],sm[MAXN],dep[MAXN];

inline void dfs(int v,int fa=0){
	FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
	dep[v] = dep[fa]+1;
	for(auto x:G[v]){
		if(x.fi == fa) continue;
		sm[x.fi] = sm[v]+x.se;
		f[x.fi][0] = v;dfs(x.fi,v);
	}
}

inline int lca(int x,int y){
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x] - dep[y];
		FOR(i,0,MAXM) if((d>>i)&1) x = f[x][i];
	}
	if(x == y) return x;
	ROF(i,MAXM,0){
		if(f[x][i] == f[y][i]) continue;
		x = f[x][i],y = f[y][i];
	}
	return f[x][0];
}

inline int dis(int x,int y){
	if(!x) x = RT;
	return sm[x]+sm[y]-2*sm[lca(x,y)];
}

int mx[MAXN],sz[MAXN],rt;
bool vis[MAXN];
int d[MAXN],sd[MAXN],ssd[MAXN],fa[MAXN],now;
// 这个点的权值 这个连通块的权值和 这个连通块到 fa 的权值*距离

inline void getroot(int v,int fa=0){
	sz[v] = 1;mx[v] = 0;
	for(auto x:G[v]){
		if(x.fi == fa || vis[x.fi]) continue;
		getroot(x.fi,v);sz[v] += sz[x.fi];
		mx[v] = std::max(mx[v],sz[x.fi]);
	}
	mx[v] = std::max(mx[v],mx[0]-sz[v]);
	if(mx[rt] > mx[v]) rt = v;
}

inline void getval(int v,int fa=0){
	sd[now] += d[v];ssd[now] += dis(::fa[now],v)*d[v];
	for(auto x:G[v]){
		if(x.fi == fa || vis[x.fi]) continue;
		getval(x.fi,v);
	}
}

inline void work(int v){
	vis[now=v] = 1;getval(v);
	for(auto x:G[v]){
		if(vis[x.fi]) continue;
		mx[rt = 0] = sz[x.fi];getroot(x.fi);
		fa[rt] = v;T[v].pb(MP(rt,x.fi));work(rt);
	}
}

inline void update(int v,int delta){
	int t = v;d[v] += delta;
	while(v){
		sd[v] += delta;
		ssd[v] += delta*dis(::fa[v],t);
		v = fa[v];
	}
}

inline int calc(int v,int ban,int mod){// 当前的分治中心 下一个分治中心 和当前分治中心相连的点
	int ans = 0,cnt = d[v];
	for(auto x:T[v]){
		if(x.fi == ban) continue;
		ans += ssd[x.fi];cnt += sd[x.fi];
	}
	d[mod] += cnt;return ans+cnt*dis(v,mod);
}

inline int query(int v,int ans){
	for(auto x:T[v]){
		if(2*sd[x.fi] < sd[v]) continue;
		int t = d[x.se],delta = calc(v,x.fi,x.se);
		int dt = d[x.se]-t;
		for(int w=x.se;w != v;w = fa[w]){
			sd[w] += dt;ssd[w] += dt*dis(fa[w],x.se);
		}
		int nans = 0;
		for(auto y:T[x.fi]) nans += ssd[y.fi];
		ans = query(x.fi,nans)+delta;
		for(int w=x.se;w != v;w = fa[w]){
			sd[w] -= dt;ssd[w] -= dt*dis(fa[w],x.se);
		}
		d[x.se] = t;return ans;
	}
	return ans;
}

int n,q;

signed main(){
	#ifdef RainAir
	freopen("../TestData/6.in","r",stdin);
	freopen("../TestData/6.ans","w",stdout);
	#endif
	scanf("%lld%lld",&n,&q);
	FOR(i,2,n){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		G[u].pb(MP(v,w));G[v].pb(MP(u,w));
	}
	dfs(1);
	mx[rt = 0] = n;getroot(1);RT = rt;
	work(rt);
	FOR(i,1,q){
		int v,w;scanf("%lld%lld",&v,&w);
		update(v,w);
		printf("%lld\n",query(RT,ssd[RT]));
	}
	return 0;
}
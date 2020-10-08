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

const int MAXN = 2e5 + 5;
int n,a[MAXN];

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

LL ans = 0;
int t[MAXN],sz[MAXN];

inline void dfs(int v,int fa=0){
	int gx = 0;sz[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		int las = t[a[v]];
		dfs(e[i].to,v);sz[v] += sz[e[i].to];
		las = t[a[v]]-las;
		las = sz[e[i].to]-las;
		ans += 1ll*las*(las-1)/2;
		gx += las;
	}
	t[a[v]] += gx+1;
}

bool vis[MAXN];

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i),vis[a[i]] = 1;
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);add(u,v);
	}
	dfs(1);
	// DEBUG(ans);
	int cnt = 0;
	// ans = -ans;
	FOR(i,1,n) if(vis[i]) ans += 1ll*(n-t[i])*(n-t[i]-1)/2,++cnt;
	printf("%lld\n",1ll*n*(n-1)*cnt/2-ans);
	return 0;
}
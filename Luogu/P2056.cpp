#pragma GCC optimize("Ofast")
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

const int MAXN = 1e5 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int a[MAXN];
int sz[MAXN],Mx[MAXN],fa[MAXN],rt;
bool vis[MAXN];
std::unordered_map<int,int> dp[MAXN];
int now;
inline void getroot(int v,int fa=0){
	sz[v] = 1;Mx[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getroot(e[i].to,v);sz[v] += sz[e[i].to];
		Mx[v] = std::max(Mx[v],sz[e[i].to]);
	}
	Mx[v] = std::max(Mx[v],Mx[0]-sz[v]);
	if(Mx[rt] > Mx[v]) rt = v;
}

std::multiset<int> bl[MAXN],mx[MAXN],ans;//每个点的答案
int dep[MAXN];

inline int gx(int v){
	if(mx[v].size() <= 1) return -1;
	auto p = mx[v].rbegin();int res = *p;
	int tt = res;
	p++;if(*p == -1) return -1;
	res += *p;
	return res;
}

inline int gx2(int v){
	if(bl[v].size() == 0) return -1;
	return *bl[v].rbegin();
}

inline void getdep(int v,int fa=0){
	dp[now][v] = dep[v];
	bl[now].insert(dp[::fa[now]][v]);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		dep[e[i].to] = dep[v] + 1;getdep(e[i].to,v);
	}
}

inline void build(int v){
	dep[v] = 0;getdep(v);
	mx[fa[v]].insert(gx2(v));
}

inline void work(int v){
	vis[now = v] = 1;build(v);
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		Mx[rt = 0] = sz[e[i].to];getroot(e[i].to,v);
		fa[rt] = v;work(rt);
	}
	mx[v].insert(0);
	ans.insert(gx(v));
}

inline void update(int v){
	int t = v;
	ans.erase(ans.find(gx(v)));
	if(a[t]) mx[v].erase(mx[v].find(0));
	else mx[v].insert(0);
	ans.insert(gx(v));
	while(v){
		if(fa[v]){
			ans.erase(ans.find(gx(fa[v])));
			mx[fa[v]].erase(mx[fa[v]].find(gx2(v)));
			if(a[t]) bl[v].erase(bl[v].find(dp[fa[v]][t]));
			else bl[v].insert(dp[fa[v]][t]);
			mx[fa[v]].insert(gx2(v));
			ans.insert(gx(fa[v]));
		}
		v = fa[v];
	}
	a[t] ^= 1;
}

int main(){
	#ifdef RainAir
	freopen("../TestData/1.in","r",stdin);
	freopen("../TestData/1.ans","w",stdout);
	#endif
	int n;scanf("%d",&n);int tt = n;
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	std::fill(a,a+n+1,1);
	Mx[rt = 0] = n;getroot(1);
	work(rt);int q;scanf("%d",&q);
	int ts = 0;
	while(q--){
		char str[23];
		scanf("%s",str);
		if(str[0] == 'G'){
//			if(++ts == 85) for(auto x:ans) DEBUG(x);
			if(tt == 0) puts("-1");
			else if(tt == 1) puts("0");
			else printf("%d\n",*ans.rbegin());
		}
		else{
			int v;scanf("%d",&v);
			update(v);
		}
	}
	return 0;
}
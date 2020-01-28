#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <cassert>
#include <map>
#include <set>

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

const int MAXN = 100000+5;
const int MAXM = 17;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int Log[MAXN];

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

std::vector<P> Opt;
std::map<P,int> S;
int tot;

inline int plus(int x,int y){
	if(x > y) std::swap(x,y);
	if(!x) return y;
	if(S.count(MP(x,y))) return S[MP(x,y)];
	Opt.pb(MP(x,y));
	S[MP(x,y)] = ++tot;
	return tot;
}

int val[MAXN],n,q;
int f[MAXN][MAXM+1],g[MAXN][MAXM+1],dep[MAXN];

inline void dfs(int v,int fa=0){
	FOR(i,1,Log[dep[v]]){
		f[v][i] = f[f[v][i-1]][i-1];
		g[v][i] = plus(g[v][i-1],g[f[v][i-1]][i-1]);
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v] + 1;
		f[e[i].to][0] = v;
		g[e[i].to][0] = plus(val[e[i].to],val[v]);
		dfs(e[i].to,v);
	}
}

inline int lca(int x,int y){
	int res = 0;
	if(x == y)return val[x];
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x]-dep[y];
		FOR(i,0,Log[d]){
			if((d>>i)&1) res = plus(res,g[x][i]),x = f[x][i];
		}
	}
	if(x == y) return res;
	ROF(i,Log[n],0){
		if(f[x][i] == f[y][i]) continue;
		res = plus(res,g[x][i]);
		res = plus(res,g[y][i]);
		x = f[x][i];y = f[y][i];
	}
	res = plus(res,g[x][0]);
	res = plus(res,g[y][0]);
	return res;
}
int ans[MAXN];

std::set<int> SS;

inline void get(int v){
	if(v <= n){
		SS.insert(v);
		return;
	}
	v -= n;
	get(Opt[v-1].fi);
	get(Opt[v-1].se);
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	scanf("%d%d",&n,&q);
	Log[0] = -1;
	FOR(i,1,MAXN-1) Log[i] = Log[i>>1]+1;
	Log[0] = 0;
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	FOR(i,1,n) val[i] = i;tot = n;
	g[1][0] = val[1];dep[1] = 1;dfs(1);
	FOR(i,1,q){
		int x,y;scanf("%d%d",&x,&y);
		ans[i] = lca(x,y);
		std::set<int> S;
		while(x != y){
			if(dep[x] < dep[y]) std::swap(x,y);
			S.insert(val[x]);x = f[x][0];
		}
		S.insert(val[x]);
		SS.clear();get(ans[i]);
		assert(S == SS);
	}
	printf("%d\n",tot);
	for(auto x:Opt) printf("%d %d\n",x.fi,x.se);
	FOR(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
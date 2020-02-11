#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
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

const int MAXN = 500+5;
const int MAXM = 1e5 + 5;

struct Edge{
	int to,nxt,cap,flow;
}e[MAXM];

int head[MAXN],cur[MAXN],cnt = 1;

inline void add(int u,int v,int cap){
	// printf("%d %d %d\n",u,v,cap);
	e[++cnt] = (Edge){v,head[u],cap,0};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

int dep[MAXN];
int S,T,n;

inline bool bfs(){
	std::queue<int> q;
	FOR(i,1,n) dep[i] = 0,cur[i] = head[i];
	q.push(S);dep[S] = 1;
	while(!q.empty()){
		int v = q.front();q.pop();
		// DEBUG(v);
		for(int i = head[v];i;i = e[i].nxt){
			if(e[i].flow < e[i].cap && !dep[e[i].to]){
				dep[e[i].to] = dep[v] + 1;
				if(e[i].to == T) return true;
				q.push(e[i].to);
			}
		}
	}
	return false;
}

inline int dfs(int v,int lim=1e9){
	if(!lim) return 0;
	if(v == T) return lim;
	int flow;
	// DEBUG(v);
	for(int &i = cur[v];i;i = e[i].nxt){
		if(e[i].flow < e[i].cap && dep[e[i].to] == dep[v] + 1){
			if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
				e[i].flow += flow;
				e[i^1].flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}

inline int Dinic(){
	int flow = 0,res = 0;
	while(bfs()){
		while((flow = dfs(S))) res += flow;
	}
	return res;
}

int p[MAXN],tmp1[MAXN],tmp2[MAXN],m;
std::vector<P> G[MAXN];

inline void work(int l,int r){
	if(r-l+1 <= 1) return;
	S = p[l],T = p[l+1];
	FOR(i,1,cnt) e[i].flow = 0;
	int t = Dinic();
	G[S].pb(MP(T,t));G[T].pb(MP(S,t));
	// DEBUG(S);DEBUG(T);DEBUG(t);
	int t1 = 0,t2 = 0;
	FOR(i,l,r){
		if(dep[p[i]]) tmp1[++t1] = p[i];
		else tmp2[++t2] = p[i];
	}
	int tot = l-1;
	FOR(i,1,t1) p[++tot] = tmp1[i];
	int mid = tot;
	FOR(i,1,t2) p[++tot] = tmp2[i];
	// assert(tot == r);
	work(l,mid);work(mid+1,r);
}

const int MAXK = 10;
int f[MAXN][MAXK+1],mn[MAXN][MAXK+1];

inline void dfs2(int v,int fa=0){
	FOR(i,1,MAXK){
		f[v][i] = f[f[v][i-1]][i-1];
		mn[v][i] = std::min(mn[v][i-1],mn[f[v][i-1]][i-1]);
	}
	FOR(i,0,(int)G[v].size()-1){
		int to = G[v][i].fi,w = G[v][i].se;
		if(to == fa) continue;
		dep[to] = dep[v] + 1;
		mn[to][0] = w;f[to][0] = v;
		dfs2(to,v);
	}
}

inline int calc(int x,int y){
	int res = 1e9;
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x]-dep[y];
		// DEBUG(d);DEBUG(x);DEBUG(y);
		FOR(i,0,MAXK) if((d>>i)&1) res = std::min(res,mn[x][i]),x = f[x][i];
	}
	// DEBUG(x);DEBUG(y);
	if(x == y) return res;
	ROF(i,MAXK,0){
		if(f[x][i] == f[y][i]) continue;
		res = std::min(res,std::min(mn[x][i],mn[y][i]));
		x = f[x][i],y = f[y][i];
	}
	res = std::min(res,std::min(mn[x][0],mn[y][0]));
	return res;
}

int main(){
	// freopen("a.in","r",stdin);
	// freopen("a.out","w",stdout);
	// DEBUG(233);
	scanf("%d%d",&n,&m);++n;
	FOR(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		++u;++v;
		add(u,v,w);add(v,u,w);
	}
	CLR(mn,0x3f);
	// DEBUG(Dinic());
	// return 0;
	FOR(i,1,n) p[i] = i;
	work(1,n);dep[1] = 1;
	dfs2(1,0);
	int q;scanf("%d",&q);
	FOR(i,1,q){
		int x,y;scanf("%d%d",&x,&y);
		++x;++y;
		// DEBUG(x);DEBUG(y);
		printf("%d\n",calc(x,y));
	}
	return 0;
}
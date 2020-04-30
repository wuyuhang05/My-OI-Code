#include <bits/stdc++.h>

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

const int MAXN = 2e5 + 5;

struct Edge{
	int u,v,w;
	Edge(int u=0,int v=0,int w=0) : u(u),v(v),w(w) {}
	
	bool operator < (const Edge &t) const {
		return w < t.w;
	}
}edge[MAXN],opt[MAXN];

struct EDge{
	int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (EDge){v,head[u]};head[u] = cnt;
}

int s[MAXN];
std::map<P,int> id;

int f[MAXN],sz[MAXN],tp;

inline int find(int x){
	return x == f[x] ? x : find(f[x]);
}

inline void merge(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	if(sz[x] < sz[y]) std::swap(x,y);
	opt[++tp] = Edge(x,y);
	f[y] = x;sz[x] += sz[y];
}

inline void undo(){
	assert(tp > 0);
	int x = opt[tp].u,y = opt[tp--].v;
	f[y] = y;sz[x] -= sz[y];
}

bool ins[MAXN];
int dfn[MAXN],low[MAXN],stk[MAXN],tp2,ts;

inline void dfs(int v){
	dfn[v] = low[v] = ++ts;ins[stk[++tp2]=v]=1;
	for(int i = head[v];i;i = e[i].nxt){
		if(!dfn[e[i].to]){
			dfs(e[i].to);low[v] = std::min(low[v],low[e[i].to]);
		}
		else if(ins[e[i].to]){
			low[v] = std::min(low[v],dfn[e[i].to]);
		}
	}
	if(low[v] == dfn[v]){
		int t = -1;
		do{
			t = stk[tp2--];
			ins[t] = 0;
			merge(t,v);
		}while(t != v);
	}
}

inline void work(int l,int r,int L,int R){
	if(l > r) return;
	if(L == R){
		FOR(i,l,r) edge[i].w = L;
		return;
	}
	int mid = (L+R)>>1;
	std::vector<int> node;
	FOR(i,l,r){
		if(edge[i].w <= mid){
			int x = edge[i].u,y = edge[i].v;
			x = find(x);y = find(y);
			add(x,y);node.pb(x);node.pb(y);
		}
	}
	for(auto x:node) ins[x] = 0;
	int lst = tp;
	for(auto x:node) if(!dfn[x]) dfs(x);
	std::vector<Edge> toL,toR;
	FOR(i,l,r){
		if(find(edge[i].u) == find(edge[i].v) && edge[i].w <= mid) toL.pb(edge[i]);
		else toR.pb(edge[i]);
	}
	int t = l-1;
	for(auto x:toL) edge[++t] = x;
	for(auto x:toR) edge[++t] = x;
	int sz = toL.size();toL.clear();toR.clear();
	cnt = ts = 0;
	for(auto x:node) dfn[x] = low[x] = head[x] = 0;
	node.clear();
	work(l+sz,r,mid,R);
	while(tp > lst) undo();
	work(l,l+sz-1,L,mid);
}

int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n) scanf("%d",s+i);
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		edge[i] = Edge(u,v,0);id[MP(u,v)] = i;
	}
	FOR(i,1,q){
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1){
			edge[id[MP(x,y)]].w = q-i+1;
		}
	}
	DEBUG(1);
	std::sort(edge+1,edge+m+1);
	work(1,m,0,q+1);
	std::sort(edge+1,edge+m+1);
	FOR(i,1,m) printf("%d %d %d\n",edge[i].u,edge[i].v,edge[i].w);
	return 0;
}
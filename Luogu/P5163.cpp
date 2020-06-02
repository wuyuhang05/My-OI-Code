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
std::vector<int> S;
namespace DS{

	LL sm[MAXN<<5];int sz[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;

	inline void pushup(int x){
		sm[x] = sm[lc[x]]+sm[rc[x]];
		sz[x] = sz[lc[x]]+sz[rc[x]];
	}

	inline void update(int &x,int l,int r,int p,int d1,int d2=1){
		if(!x) x = ++tot;
		if(l == r){
			sm[x] += d1;sz[x] += d2;
			return;
		}
		int mid = (l + r) >> 1;
		if(p <= mid) update(lc[x],l,mid,p,d1,d2);
		else update(rc[x],mid+1,r,p,d1,d2);
		pushup(x);
	}

	inline LL query(int x,int l,int r,int k){
		if(!x) return 0;
		if(l == r) return 1ll*std::min(k,sz[x])*S[l-1];
		int mid = (l + r) >> 1;
		if(k < sz[rc[x]]) return query(rc[x],mid+1,r,k);
		else if(k == sz[rc[x]]) return sm[rc[x]];
		else return sm[rc[x]]+query(lc[x],l,mid,k-sz[rc[x]]);
	}

	inline int Merge(int x,int y,int l,int r){
		if(!x || !y) return x+y;
		if(l == r){
			sz[x] += sz[y];
			sm[x] += sm[y];
			return x;
		}
		int mid = (l + r) >> 1;
		lc[x] = Merge(lc[x],lc[y],l,mid);
		rc[x] = Merge(rc[x],rc[y],mid+1,r);
		pushup(x);
		return x;
	}
}

using DS::query;
using DS::update;
using DS::Merge;
using DS::root;

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
	for(auto x:node) assert(ins[x] == 0);
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
	assert(t == r);
	int sz = toL.size();toL.clear();toR.clear();
	cnt = ts = 0;
	for(auto x:node) dfn[x] = low[x] = head[x] = 0;
	node.clear();
	// DEBUG(l);DEBUG(sz);DEBUG(r);
	// DEBUG(L);DEBUG(mid);DEBUG(R);
	work(l+sz,r,mid+1,R);
	while(tp > lst) undo();
	work(l,l+sz-1,L,mid);
}

struct Query{
	int opt,x,y,id;
	Query(int opt=0,int x=0,int y=0,int id=0) : opt(opt),x(x),y(y),id(id) {}
	bool operator < (const Query &t) const {
		if(t.id != id) return id < t.id;
		return opt<t.opt;
	}
};
std::vector<Query> qry;
LL ans[MAXN];

inline int pos(int x){
	return std::lower_bound(all(S),x)-S.begin()+1;
}

int main(){
	int n,m,q;
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n) scanf("%d",s+i),f[i] = i,sz[i] = 1,S.pb(s[i]);
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		edge[i] = Edge(u,v,0);id[MP(u,v)] = i;
	}
	FOR(i,1,q){
		ans[i] = -666;
		int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
		if(opt == 1){
			edge[id[MP(x,y)]].w = q-i+1;
		}
		if(opt == 2){
			s[x] += y;S.pb(s[x]);
			qry.pb(Query(2,x,y,q-i+1));
		}
		if(opt == 3){
			qry.pb(Query(3,x,y,q-i+1));
			ans[i] = 0;
		}
	}
	work(1,m,0,q+1);
	FOR(i,1,m)
		qry.pb(Query(1,edge[i].u,edge[i].v,edge[i].w));
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	int M = S.size();
	std::sort(all(qry));
	FOR(i,1,n){
		f[i] = i;
		update(root[i],1,M,pos(s[i]),s[i]);
	}
	for(auto x:qry){
		if(x.opt == 1){
			int xx = find(x.x),yy = find(x.y);
			if(xx == yy) continue;
			if(sz[xx] < sz[yy]) std::swap(xx,yy);
			merge(xx,yy);Merge(root[xx],root[yy],1,M);
		}
		if(x.opt == 2){
			update(root[find(x.x)],1,M,pos(s[x.x]),-s[x.x],-1);
			s[x.x] -= x.y;
			update(root[find(x.x)],1,M,pos(s[x.x]),s[x.x]);
		}
		if(x.opt == 3){
			ans[q-x.id+1] = query(root[find(x.x)],1,M,x.y);
		}
	}
	FOR(i,1,q){
		if(ans[i] != -666) printf("%lld\n",ans[i]);
	}
	return 0;
}
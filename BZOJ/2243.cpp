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
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const int MAXM = 17;

int n,m;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int val[MAXN];

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dfn[MAXN],dep[MAXN],sz[MAXN],tp[MAXN],son[MAXN],nfd[MAXN],fa[MAXN];
int f[MAXN][MAXM+1];

inline void dfs1(int v){
	sz[v] = 1;
	f[v][0] = fa[v];
	FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa[v]) continue;
		dep[e[i].to] = dep[v] + 1;
		fa[e[i].to] = v;
		dfs1(e[i].to);sz[v] += sz[e[i].to];
		son[v] = sz[son[v]] < sz[e[i].to] ? e[i].to : son[v];
	}
}

inline void dfs2(int v,int tp=1){
	static int ts = 0;dfn[v] = ++ts;nfd[ts] = v;
	::tp[v] = tp;
	if(son[v]) dfs2(son[v],tp);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa[v] || e[i].to == son[v]) continue;
		dfs2(e[i].to,e[i].to);
	}
}

struct Node{
	int ls,rs,ans;

	Node(int ls=0,int rs=0,int ans=0) : ls(ls),rs(rs),ans(ans) {}

	friend Node operator + (const Node &a,const Node &b){
		Node res;
		res.ans = a.ans + b.ans;
		res.ls = a.ls;res.rs = b.rs;
		if(a.rs == b.ls) res.ans--;
		return res;
	}
}sm[MAXN<<2];
int tag[MAXN<<2];

#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
	sm[x] = sm[lc] + sm[rc];
}

inline void cover(int x,int d){
	sm[x].ans = 1;sm[x].ls = sm[x].rs = d;
	tag[x] = d;
}

inline void pushdown(int x){
	if(tag[x] != -1){
		cover(lc,tag[x]);
		cover(rc,tag[x]);
		tag[x] = -1;
	}
}

inline void build(int x,int l,int r){
	tag[x] = -1;
	if(l == r){
		sm[x] = Node(val[nfd[l]],val[nfd[r]],1);
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

inline void modify(int x,int l,int r,int L,int R,int d){
	if(l == L && r == R){
		cover(x,d);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(x);
	if(R <= mid) modify(lc,l,mid,L,R,d);
	else if(L > mid) modify(rc,mid+1,r,L,R,d);
	else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
	pushup(x);
}

inline Node query(int x,int l,int r,int L,int R){
	if(l == L && r == R) return sm[x];
	pushdown(x);
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc,l,mid,L,R);
	if(L > mid) return query(rc,mid+1,r,L,R);
	return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

inline void modify(int x,int y,int d){
	while(tp[x] != tp[y]){
		if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
		modify(1,1,n,dfn[tp[x]],dfn[x],d);
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) std::swap(x,y);
	modify(1,1,n,dfn[x],dfn[y],d);
}

inline Node calc(int x,int y){
	bool flag = dep[x] < dep[y];
	// puts("233");
	std::vector<Node> S;
	while(tp[x] != tp[y]){
		if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
		Node t = query(1,1,n,dfn[tp[x]],dfn[x]);
		if(!flag) std::swap(t.ls,t.rs);
		S.pb(t);
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) std::swap(x,y);
	Node t = query(1,1,n,dfn[x],dfn[y]);
	if(!flag) std::swap(t.ls,t.rs);
	S.pb(t);
	if(flag) std::reverse(all(S));
	// for(auto x:S) printf("%d %d %d\n",x.ans,x.ls,x.rs);
	Node res = S[0];
	FOR(i,1,(int)S.size()-1) res = res+S[i];
	return res;
}

inline int lca(int x,int y){
	while(tp[x] != tp[y]){
		if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) std::swap(x,y);
	return x;
}

inline int kth(int x,int k){
	FOR(i,0,MAXM){
		if((k>>i)&1) x = f[x][i];
	}
	return x;
}

inline Node query(int x,int y){
	if(dep[x] < dep[y]) std::swap(x,y);
	int l = lca(x,y);
	Node ls = calc(x,l);
	// DEBUG(ls.ls);DEBUG(ls.rs);
	if(l == y) return ls;
	Node rs = calc(kth(y,dep[y]-dep[l]-1),y);
	// DEBUG(ls.ls);DEBUG(ls.rs);DEBUG(ls.ans);
	Node res = ls+rs;
	return res;
}

int main(){
	// freopen("3.in","r",stdin);
	// freopen("3","w",stdout);
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",val+i);
	FOR(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dep[1] = 1;dfs1(1);dfs2(1);build(1,1,n);
	// DEBUG(query(1,1,n,1,2).ans);
	// return 0;
	FOR(i,1,m){
		char str[3];
		scanf("%s",str);
		if(str[0] == 'C'){
			int u,v,w;scanf("%d%d%d",&u,&v,&w);
			modify(u,v,w);
		}
		if(str[0] == 'Q'){
			int u,v;scanf("%d%d",&u,&v);
			printf("%d\n",query(u,v).ans);
		}
	}
	return 0;
}
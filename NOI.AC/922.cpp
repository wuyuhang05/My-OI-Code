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

const int MAXN = 2e6 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dfn[MAXN],sz[MAXN],son[MAXN],fa[MAXN],dep[MAXN],nfd[MAXN],tp[MAXN];

inline void dfs1(int v){
	sz[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa[v]) continue;
		dep[e[i].to] = dep[v] + 1;
		dfs1(e[i].to);sz[v] += sz[e[i].to];
		son[v] = sz[son[v]] < sz[e[i].to] ? e[i].to : son[v];
	}
}

inline void dfs2(int v,int tp){
	static int ts = 0;
	dfn[v] = ++ts;nfd[ts] = v;::tp[v] = tp;
	if(son[v]) dfs2(son[v],tp);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa[v] || e[i].to == son[v]) continue;
		dfs2(e[i].to,e[i].to);
	}
}

LL sm[MAXN<<2],coe[MAXN<<2];
int tag[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
	sm[x] = sm[lc]+sm[rc];
}

inline void cover(int x,int d){
	sm[x] += d*coe[x];
	tag[x] += d;
}

inline void pushdown(int x){
	if(tag[x]){
		cover(lc,tag[x]);
		cover(rc,tag[x]);
		tag[x] = 0;
	}
}

inline void build(int x,int l,int r){
	tag[x] = sm[x] = 0;
	if(l == r){
		coe[x] = 2*dep[nfd[l]]-1;
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	coe[x] = coe[lc]+coe[rc];
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

inline LL query(int x,int l,int r,int L,int R){
	if(l == L && r == R) return sm[x];
	int mid = (l + r) >> 1;
	pushdown(x);
	if(R <= mid) return query(lc,l,mid,L,R);
	if(L > mid) return query(rc,mid+1,r,L,R);
	return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int n;

inline void modify(int x,int y,int d){
	while(tp[x] != tp[y]){
		if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
		modify(1,1,n,dfn[tp[x]],dfn[x],d);
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) std::swap(x,y);
	modify(1,1,n,dfn[x],dfn[y],d);
}

inline LL query(int x,int y){
	LL res = 0;
	while(tp[x] != tp[y]){
		if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
		res += query(1,1,n,dfn[tp[x]],dfn[x]);
		x = fa[tp[x]];
	}
	if(dep[x] > dep[y]) std::swap(x,y);
	res += query(1,1,n,dfn[x],dfn[y]);
	return res;
}

int main(){
	scanf("%d",&n);
	FOR(i,2,n){
		int f;scanf("%d",&f);
		fa[i] = f;
		add(f,i);
	}
	dep[1] = 1;dfs1(1);dfs2(1,1);build(1,1,n);
	FOR(i,1,n){
		int x;scanf("%d",&x);
		modify(i,1,1);
		printf("%lld\n",query(x,1));
	}
	return 0;
}
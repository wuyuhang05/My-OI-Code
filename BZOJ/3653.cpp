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

const int MAXN = 3e5 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int sz[MAXN],dep[MAXN],dfn[MAXN],nfd[MAXN];
int n,q;

// 查询 dfn[i] \in [l,r] dep[i] \in [a,b]
// 按照 dfn 建立主席树

LL sm[MAXN<<5];
int lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;

inline void insert(int prev,int &v,int l,int r,int p,int d){
	sm[v=++tot] = sm[prev]+d;lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc[prev],lc[v],l,mid,p,d);
	else insert(rc[prev],rc[v],mid+1,r,p,d);
}

inline LL query(int x,int y,int l,int r,int L,int R){
	if(l == L && r == R) return sm[y]-sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],lc[y],l,mid,L,R);
	if(L > mid) return query(rc[x],rc[y],mid+1,r,L,R);
	return query(lc[x],lc[y],l,mid,L,mid)+query(rc[x],rc[y],mid+1,r,mid+1,R);
}

inline void dfs(int v,int fa=0){
	sz[v] = 1;
	static int ts = 0;
	dfn[v] = ++ts;nfd[ts] = v;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v] + 1;
		dfs(e[i].to,v);
		sz[v] += sz[e[i].to];
	}
}

int main(){
	scanf("%d%d",&n,&q);
	FOR(i,1,n-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	dep[1] = 1;dfs(1);
	FOR(i,1,n) insert(root[i-1],root[i],1,n,dep[nfd[i]],sz[nfd[i]]-1);
	FOR(i,1,q){
		int p,k;scanf("%d%d",&p,&k);
		LL ans = 0;
		ans += 1ll*(sz[p]-1)*std::min(dep[p]-1,k);
		ans += query(root[dfn[p]],root[dfn[p]+sz[p]-1],1,n,dep[p],std::min(n,dep[p]+k));
		printf("%lld\n",ans);
	}
	return 0;
}
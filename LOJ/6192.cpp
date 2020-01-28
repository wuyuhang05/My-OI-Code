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
const int MAXM = 19;
int n,q;
int a[MAXN];
int dep[MAXN];

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN][MAXM+1];
std::vector<P> qqq[MAXN];
int M;

struct Query{
	int u,v,c,fst;
}qu[MAXN];

int mn[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],root[MAXN],tot;

inline void update(int prev,int &v,int l,int r,int p,int d){
	mn[v = ++tot] = mn[prev];
	if(dep[d] >= dep[mn[v]]) mn[v] = d;
	lc[v] = lc[prev];rc[v] = rc[prev];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc[prev],lc[v],l,mid,p,d);
	else update(rc[prev],rc[v],mid+1,r,p,d);
}

inline int query(int x,int l,int r,int L,int R){
	if(l == L && r == R) return mn[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc[x],l,mid,L,R);
	if(L > mid) return query(rc[x],mid+1,r,L,R);
	int ls = query(lc[x],l,mid,L,mid),rs = query(rc[x],mid+1,r,mid+1,R);
	if(dep[ls] < dep[rs]) std::swap(ls,rs);
	return ls;
}

inline void dfs(int v,int fa=0){
	update(root[fa],root[v],1,M,a[v],v);
	int t = query(root[v],1,M,a[v]+1,M);
	f[v][0] = t;
	FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
	for(auto x:qqq[v]){
		int t = query(root[v],1,M,x.fi+1,M);
		qu[x.se].fst = t;
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v] + 1;
		dfs(e[i].to,v);
	}
}

inline int query(int x,int y){ 
	if(dep[x] < dep[y]) std::swap(x,y);
	int ans = 0;
	ROF(i,MAXM,0){
		if(dep[f[x][i]] < dep[y]) continue;
		ans += (1<<i);x = f[x][i];
	}
	return ans;
}

int main(){
	scanf("%d%d",&n,&q);
	FOR(i,1,n) scanf("%d",a+i),M = std::max(M,a[i]);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	FOR(i,1,q){
		scanf("%d%d%d",&qu[i].u,&qu[i].v,&qu[i].c);
		M = std::max(M,qu[i].c);
		qqq[qu[i].u].pb(MP(qu[i].c,i));
	}
	++M;
	dep[1] = 1;dfs(1);
	FOR(i,1,q){
		int u = qu[i].v,v = qu[i].fst,ans = 1;
		if(dep[v] < dep[u]){
			puts("0");
			continue;
		}
		ans += query(u,v);
		printf("%d\n",ans);
	}
	return 0;
}
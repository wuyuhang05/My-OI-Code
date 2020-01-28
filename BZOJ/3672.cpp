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
#define int LL
#define double long double
const int MAXN = 2e5 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int p[MAXN],q[MAXN],l[MAXN];
int n;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	// e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int mx[MAXN],sz[MAXN];
int root,size;
bool del[MAXN];

inline void getroot(int v,int fa=0){
	sz[v] = 1;mx[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || del[e[i].to]) continue;
		getroot(e[i].to,v);
		sz[v] += sz[e[i].to];
		mx[v] = std::max(mx[v],sz[e[i].to]);
	}
	mx[v] = std::max(mx[v],size-sz[v]);
	if(!root || mx[root] >= mx[v]) root = v;
}

int f[MAXN];
int dis[MAXN];
std::vector<int> S;

inline void dfs(int v,int fa=0){
	S.pb(v);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || del[e[i].to]) continue;
		dfs(e[i].to,v);
	}
}

inline void getdis(int v,int fa=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || del[e[i].to]) continue;
		dis[e[i].to] = dis[v] + e[i].w;
		getdis(e[i].to,v);
	}
}

inline bool cmp(int x,int y){
	return dis[x]-l[x] > dis[y]-l[y];
}

int st[MAXN],tp;
int fa[MAXN];
#define X(i) (dis[i])
#define Y(i) (f[i])
double sl[MAXN];

inline double slope(int x,int y){
	return 1.0*(double)(Y(y)-Y(x))/(double)(X(y)-X(x));
}

inline void insert(int x){
	while(tp >= 2 && sl[tp-1] <= slope(st[tp],x)) tp--;
	st[++tp] = x;sl[tp-1] = slope(st[tp-1],x);
	sl[tp] = -1e18;
}

inline int query(double d){
	int l = 1,r = tp,ans = -1;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(sl[mid] <= d) r = mid-1,ans = mid;
		else l = mid+1;
	}
	// FOR(i,1,tp) printf("%d %.10f\n",st[i],(Y(st[i])-d*X(st[i])));
	// printf("RES:%.10f\n",(Y(st[ans])-d*X(st[ans])));
	return st[ans];
}

inline void work(int v,int SZ){
	if(SZ == 1) return;
	root = 0;size = SZ;getroot(v);
	int rt = root;
	// FOR(i,1,n) printf("%d ",del[i]);puts("");
	for(int i = head[rt];i;i = e[i].nxt) SZ -= sz[e[i].to],del[e[i].to] = 1;
	// exit(0);
	// DEBUG(SZ);
	work(v,SZ);
	S.clear();
	for(int i = head[rt];i;i = e[i].nxt) dfs(e[i].to);
	std::sort(all(S),cmp);
	int t = rt;tp = 0;int ep = fa[v];
	FOR(i,0,(int)S.size()-1){
		int v = S[i];
		while(t != ep && dis[v]-dis[t] <= l[v]){
			insert(t);
			t = fa[t];
		}
		if(tp){
			int j = query(p[v]);
			f[v] = std::min(f[v],f[j]+(dis[v]-dis[j])*p[v]+q[v]);
		}
	}
	for(int i = head[rt];i;i = e[i].nxt){
		work(e[i].to,sz[e[i].to]);
	}
}

signed main(){
	// freopen("2.in","r",stdin);
	// freopen("2.out","w",stdout);
	scanf("%lld%*lld",&n);
	FOR(i,2,n){
		int w;scanf("%lld%lld%lld%lld%lld",fa+i,&w,p+i,q+i,l+i);
		add(fa[i],i,w);
	}
	FOR(i,2,n) f[i] = 1e18;
	getdis(1);
	work(1,n);
	FOR(i,2,n) printf("%lld\n",f[i]);
	return 0;
}
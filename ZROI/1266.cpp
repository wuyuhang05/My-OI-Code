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
#define P std::pair<LL,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 4e5 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int root,sz[MAXN],mx[MAXN];
bool vis[MAXN];

inline void getroot(int v,int fa=0){
	sz[v] = 1;mx[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getroot(e[i].to,v);
		sz[v] += sz[e[i].to];mx[v] = std::max(mx[v],sz[e[i].to]);
	}
	mx[v] = std::max(mx[v],mx[0]-sz[v]);
	if(mx[root] > mx[v]) root = v;
}
LL dis[MAXN];
std::vector<P> S;
inline void dfs(int v,int id,int fa=0){
	S.pb(MP(dis[v],id));
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dis[e[i].to] = dis[v] + e[i].w;
		dfs(e[i].to,id,v);
	}
}
int ct[MAXN];

inline bool cmp(const P &a,const P &b){
	return a.fi > b.fi;
}

inline int getsz(int v,int fa=0){
	int res = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		res += getsz(e[i].to,v);
	}
	return res;
}

int n,k;
inline void work(int v){
	root = 0;mx[0] = getsz(v,0);getroot(v);v = root;
	vis[v] = 1;int tot = 0;S.clear();//DEBUG(v);
	S.pb(MP(0,0));
	for(int i = head[v];i;i = e[i].nxt){
		dis[e[i].to] = e[i].w;dfs(e[i].to,e[i].to,v);
	}
	std::nth_element(S.begin(),S.begin()+k-1,S.end(),cmp);
	FOR(i,0,n) ct[i] = 0;
	int to = 0;
	FOR(i,0,k-1){
		ct[S[i].se]++;
		if(ct[S[i].se] > k/2){
			to = S[i].se;break;
		}
	}
	if(to && !vis[to]) work(to);
	else{
		std::sort(all(S),cmp);
		FOR(i,0,n) ct[i] = 0;LL res = 0;
		int t = 0;
		for(auto x:S){
			ct[x.se]++;
			if(ct[x.se] > k/2) continue;
			res += x.fi;
			if(++t == k) break;
		}
		printf("%lld\n",res*2);exit(0);
	}
}

int main(){
	scanf("%d%d",&n,&k);
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);add(u,v,w);
	}
	sz[1] = n;work(1);
	return 0;
}
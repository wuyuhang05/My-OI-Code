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
const int MAXN = 2e5 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt;
int n,k;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int val[MAXN];
std::vector<int> S;
int tot;
int len[MAXN],son[MAXN];
int sm[MAXN];

inline void dfs(int v,int fa=0){
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs(e[i].to,v);
		son[v] = len[e[i].to] > len[son[v]] ? e[i].to : son[v];
	}
	len[v] = len[son[v]]+val[v];
}

inline void dfs2(int v,int tp,int fa=0){
	sm[tp] += val[v];
	if(son[v]) dfs2(son[v],tp,v);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || e[i].to == son[v]) continue;
		dfs2(e[i].to,++tot,v);
	}
}

signed main(){
	scanf("%lld%lld",&n,&k);
	FOR(i,1,n) scanf("%lld",val+i);
	FOR(i,1,n-1){
		int u,v;scanf("%lld%lld",&u,&v);
		add(u,v);
	}
	dfs(1);
	dfs2(1,tot=1);
	std::sort(sm+1,sm+tot+1);
	std::reverse(sm+1,sm+tot+1);
	int ans = 0;
	FOR(i,1,k) ans += sm[i];
	printf("%lld\n",ans);
	return 0;
}
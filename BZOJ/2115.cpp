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

const int MAXN = 2e5 + 5;
const int MAXK = 62;

struct Edge{
	int to;LL w;int nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,LL w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

LL base[MAXK+1];

inline void insert(LL x){
	ROF(i,MAXK,0){
		if((x>>i)&1){
			if(base[i]) x ^= base[i];
			else{
				base[i] = x;return;
			}
		}
	}
}

LL dis[MAXN];bool vis[MAXN];
inline void dfs(int v,int fa=0){
	vis[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		if(vis[e[i].to]){
			insert(dis[v]^dis[e[i].to]^e[i].w);
		}
		else{
			dis[e[i].to] = dis[v]^e[i].w;
			dfs(e[i].to,v);
		}
	}
}

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		int u,v;LL w;scanf("%d%d%lld",&u,&v,&w);
		add(u,v,w);
	}
	dfs(1,0);
	LL ans = dis[n];
	ROF(i,MAXK,0){
		ans = std::max(ans,ans^base[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
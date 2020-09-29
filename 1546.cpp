#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int MAXN = 1e5 +5;
int n,m;
struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int dep[MAXN],mx;

inline void dfs(int v,int fa=0){
	mx = std::max(mx,dep[v]);
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dep[e[i].to] = dep[v]+1;dfs(e[i].to,v);
	}
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);add(u,v);
	}
	dfs(1);
	printf("%d\n",m <= mx ? m+1 : std::min(n,mx+((m-mx)>>1)+1));
	return 0;
}
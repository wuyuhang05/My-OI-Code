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

const int MAXN = 5e5 + 5;
const int MAXK = 20 + 5;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int f[MAXN][MAXK],g[MAXN][MAXK];
int n,k;
int val[MAXN];
bool vis[MAXN];

inline void merge(int x,int y){
	FOR(i,0,k) g[x][i] = std::min(f[y][i]+g[x][i],g[y][i+1]+f[x][i+1]);
	ROF(i,k-1,0) g[x][i] = std::min(g[x][i],g[x][i+1]);
	f[x][0] = g[x][0];
	FOR(i,1,k+1) f[x][i] += f[y][i-1];
	FOR(i,1,k+1) f[x][i] = std::min(f[x][i],f[x][i-1]);
}

inline void dfs(int v,int fa=0){
	if(vis[v]) f[v][0] = g[v][0] = val[v];
	FOR(i,1,k) g[v][i] = val[v];
	// if(v == 2) DEBUG(g[2][1]);
	g[v][k+1] = 1e9+7;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs(e[i].to,v);
		merge(v,e[i].to);
	}
}

int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,n) scanf("%d",val+i);
	int m;scanf("%d",&m);
	FOR(i,1,m) {int x;scanf("%d",&x);vis[x] = 1;}
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs(1);
	// DEBUG(f[4][0]);
	// FOR(i,0,k) DEBUG(g[2][i]);
	printf("%d\n",f[1][0]);
	return 0;
}
/*
f[v][i] 表示 v 子树还有最多往下 i 层没有覆盖的代价
g[v][i] 表示 v 子树还能最少往上覆盖 i 层的代价
因为并不存在原定义下的 g[v][i] <= g[v][i+1]
合并子树 x y,y \in son[x]
f[x][i]+f[y][i-1] -> f'[x][i]
f[y][i-1]+g[x][i] -> g'[x][i]
g[y][i+1]+f[x][i] -> g'[x][i]

*/
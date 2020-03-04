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

const int MAXN = 3000+5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;
int n,k;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int f[3][MAXN][MAXN],sz[MAXN];
/*
0: 连通块最小值
1: 直径不跨过v
2: 跨过
 */

inline void merge(int x,int y,int w){
	ROF(i,std::min(sz[x],k),1){
		ROF(j,std::min(sz[y],k),1){
			if(i+j > k) continue;
			f[0][x][i+j] = std::min(f[0][x][i+j],f[0][x][i]+f[0][y][j]+w);
			f[1][x][i+j] = std::min(f[1][x][i+j],std::min(f[1][x][i]+(f[0][y][j]+w)*2,f[1][y][j]+2*f[0][x][i]+w));
			f[2][x][i+j] = std::min(f[2][x][i+j],std::min(f[2][x][i]+(f[0][y][j]+w)*2,std::min(f[2][y][j]+(f[0][x][i]+w)*2,f[1][x][i]+f[1][y][j]+w)));
		}
	}
	sz[x] += sz[y];
}

inline void dfs(int v,int fa=0){
	sz[v] = 1;f[0][v][1] = f[1][v][1] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs(e[i].to,v);merge(v,e[i].to,e[i].w);
	}
}

int main(){
	scanf("%d%d",&n,&k);
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	CLR(f,0x3f);
	dfs(1);
	int ans = 1e9;
	FOR(i,1,n){
		ans = std::min(ans,std::min(f[1][i][k],f[2][i][k]));
	}
	printf("%d\n",ans);
	return 0;
}
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

const int MAXN = 65536+1;
const int MAXM = 16;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

std::vector<int> T[MAXN];
int n,du[MAXN];
int f[MAXN][MAXM+1];
std::vector<int> food[MAXN];
int dep[MAXN];

inline int lca(int x,int y){
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x] - dep[y];
		FOR(i,0,MAXM){
			if((d>>i)&1) x = f[x][i];
		}
	}
	if(x == y) return x;
	ROF(i,MAXM,0){
		if(f[x][i] == f[y][i]) continue;
		x = f[x][i],y = f[y][i];
	}
	return f[x][0];
}

inline void topsort(){
	std::queue<int> q;
	dep[0] = 1;
	FOR(i,1,n) if(!du[i]) q.push(i),dep[i] = 2;
	while(!q.empty()){
		int v = q.front();q.pop();
		f[v][0] = food[v].empty() ? 0 : food[v][0];
		FOR(i,1,(int)food[v].size()-1){
			f[v][0] = lca(f[v][0],food[v][i]);
		}
		T[f[v][0]].pb(v);dep[v] = dep[f[v][0]]+1;
		FOR(i,1,MAXM){
			f[v][i] = f[f[v][i-1]][i-1];
		}
		for(int i = head[v];i;i = e[i].nxt){
			if(!--du[e[i].to]){
				q.push(e[i].to);
			}
		}
	}
}

int sz[MAXN];

inline void dfs(int v,int fa=0){
	sz[v] = 1;
	FOR(i,0,(int)T[v].size()-1){
		int x = T[v][i];
		if(x == fa) continue;
		dfs(x,v);
		sz[v] += sz[x];
	}
}

int main(){
	// freopen("9.in","r",stdin);
	// freopen("9.ans","w",stdout);
	scanf("%d",&n);
	// DEBUG(n);
	FOR(i,1,n){
		int x;scanf("%d",&x);
		while(x){
			add(x,i);du[i]++;
			food[i].pb(x);
			scanf("%d",&x);
		}
	}
	topsort();
	// FOR(i,0,(int)root.size()-1) dfs(root[i],0);
	dfs(0);
	// DEBUG(count);
	FOR(i,1,n) printf("%d\n",sz[i]-1);
	return 0;
}
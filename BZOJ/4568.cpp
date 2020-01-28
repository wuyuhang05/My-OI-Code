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
const int MAXN = 2e4 + 5;
const int MAXM = 61;
const int MAXK = 15;

struct Edge{
	int to,nxt;
}e[MAXN<<1];

int head[MAXN],cnt,dep[MAXN];

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

struct Node{
	int a[MAXM+1],tot;
	Node(){
		CLR(a,0);tot = 0;
	}

	inline void insert(int x){
		ROF(i,MAXM,0){
			if((x>>i)&1){
				if(a[i]) x ^= a[i];
				else{
					a[i] = x;
					return;
				}
			}
		}
	}
}lb[MAXN][MAXK+1];
int f[MAXN][MAXK+1];
int val[MAXN];

inline Node merge(Node a,const Node &b){
	FOR(i,0,MAXM) if(b.a[i]) a.insert(b.a[i]);
	return a;
}

inline void dfs(int v,int fa=0){
	FOR(i,1,MAXK){
		f[v][i] = f[f[v][i-1]][i-1];
		lb[v][i] = merge(lb[v][i-1],lb[f[v][i-1]][i-1]);
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		f[e[i].to][0] = v;
		lb[e[i].to][0].insert(val[v]);
		dep[e[i].to] = dep[v] + 1;
		dfs(e[i].to,v);
	}
}

inline Node query(int x,int y){
	Node res;
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x]-dep[y];
		FOR(i,0,MAXK){
			if((d>>i)&1){
				res = merge(res,lb[x][i]);
				x = f[x][i];
			}
		}
	}
	if(x == y) return res;
	ROF(i,MAXK,0){
		if(f[x][i] == f[y][i]) continue;
		res = merge(res,lb[x][i]);
		res = merge(res,lb[y][i]);
		x = f[x][i],y = f[y][i];
	}
	res = merge(res,lb[x][0]);
	res = merge(res,lb[y][0]);
	return res;
}

int n,q;

signed main(){
	scanf("%lld%lld",&n,&q);
	FOR(i,1,n) scanf("%lld",val+i);
	FOR(i,2,n){
		int u,v;scanf("%lld%lld",&u,&v);
		add(u,v);
	}
	FOR(i,1,n) lb[i][0].insert(val[i]);
	dep[1] = 1;dfs(1);
	FOR(i,1,q){
		int x,y;scanf("%lld%lld",&x,&y);
		if(x == y) printf("%lld\n",val[x]);
		else{
			Node res = query(x,y);
			int ans = 0;
			ROF(i,MAXM,0) ans = std::max(ans,ans^res.a[i]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
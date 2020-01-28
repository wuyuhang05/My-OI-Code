/*
 * Time: 2019-12-04 13:15:30
 */
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

const int MAXN = 200+5;
const int MAXM = 2000+5;

struct Edge{
	int to,nxt,cap,flow;
}e[MAXM<<1];

int head[MAXN],cur[MAXN],cnt = 1;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,head[u],w,0};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v],0,0};head[v] = cnt;
}

int dep[MAXN],S,T,n,m;

inline bool bfs(){
	FOR(i,1,n) dep[i] = 0,cur[i] = head[i];
	std::queue<int> q;q.push(S);dep[S] = 1;
	while(!q.empty()){
		int v = q.front();q.pop();
		for(int i = head[v];i;i = e[i].nxt){
			if(e[i].flow < e[i].cap && !dep[e[i].to]){
				dep[e[i].to] = dep[v] + 1;
				if(e[i].to == T) return true;
				q.push(e[i].to);
			}
		}
	}
	return false;
}

inline int dfs(int v,int lim=1e9){
	if(!lim) return 0;
	if(v == T) return lim;
	int flow;
	for(int &i = cur[v];i;i = e[i].nxt){
		if(e[i].flow < e[i].cap && dep[e[i].to] == dep[v] + 1){
			if((flow = dfs(e[i].to,std::min(lim,e[i].cap-e[i].flow)))){
				e[i].flow += flow;
				e[i^1].flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}

inline int Dinic(){
	int res = 0,flow;
	while(bfs()){
		while((flow = dfs(S))) res += flow;
	}
	return res;
}

inline void clear(){
	cnt = 1;FOR(i,1,n) head[i] = 0;
}

inline void Solve(){
	scanf("%d%d%d%d",&n,&m,&S,&T);
	// DEBUG(m);
	FOR(i,1,m){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w*(m+1)+1);
	}
	int ans = Dinic();
	ans %= (m+1);
	printf("%d\n",ans);
	clear();
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}

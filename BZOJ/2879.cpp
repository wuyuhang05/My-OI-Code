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
const int MAXN = 1e5 + 5;
const int MAXM = 800+5;

struct Edge{
	int from,to,nxt,flow,cap,w;
}e[MAXN<<1];
int head[MAXN],cnt = 1;

inline void add(int u,int v,int cap,int w){
	// printf("%d %d %d %d\n",u,v,cap,w);
	e[++cnt] = (Edge){u,v,head[u],0,cap,w};head[u] = cnt;
	e[++cnt] = (Edge){v,u,head[v],0,0,-w};head[v] = cnt;
}

int pre[MAXN],dis[MAXN],inq[MAXN];

int S,T,N;

inline bool spfa(){
	std::queue<int> q;q.push(S);
	FOR(i,1,N) dis[i] = 1e9,pre[i] = 0;
	dis[S] = 0;inq[S] = 1;
	while(!q.empty()){
		int v = q.front();q.pop();inq[v] = false;
		for(int i = head[v];i;i = e[i].nxt){
			if(e[i].cap > e[i].flow && dis[e[i].to] > dis[v] + e[i].w){
				dis[e[i].to] = dis[v] + e[i].w;
				pre[e[i].to] = i;
				if(!inq[e[i].to]) q.push(e[i].to),inq[e[i].to] = true;
			}
		}
	}
	return pre[T];
}

int maxFlow,minCost;
int n,m,tot;// n 菜 m 厨师

inline int calc1(int i,int j){ // 第 i 个厨师处理第 j 个菜
	return (i-1)*tot+j;
}

inline int calc2(int i){ // 第 i 个菜
	return calc1(m,tot)+i;
}
int a[MAXM][MAXM],c[MAXN]; // i 厨师做 j 菜
bool vis[MAXM][MAXM];

inline void work(){
	while(spfa()){
		// DEBUG(minCost);
		int flow = 1e9,v = T;
		while(v != S){
			flow = std::min(flow,e[pre[v]].cap-e[pre[v]].flow);
			v = e[pre[v]].from;
		}
		maxFlow += flow;v = T;int t = -1;
		while(v != S){
			minCost += flow*e[pre[v]].w;
			e[pre[v]].flow += flow;
			e[pre[v]^1].flow -= flow;
			if(e[pre[v]].from == S) t = v;
			v = e[pre[v]].from;
		}
		// DEBUG(t);
		int t1 = (t-1)/tot+1,t2 = t%tot+1;
		if(vis[t1][t2]) continue;
		vis[t1][t2] = 1;
		add(S,calc1(t1,t2),1,0);
		FOR(i,1,n){
			add(calc1(t1,t2),calc2(i),1,(t2)*a[t1][i]);
			// DEBUG(t1);DEBUG(t2);
		}
	}
}

signed main(){
	scanf("%d%d",&n,&m);
	// DEBUG(1);
	FOR(i,1,n) scanf("%d",c+i),tot += c[i];
	FOR(i,1,n){
		FOR(j,1,m){
			scanf("%d",&a[j][i]);
		}
	}
	S = calc2(n)+1,T = calc2(n)+2,N = T;
	FOR(i,1,n) add(calc2(i),T,c[i],0);
	FOR(i,1,m) add(S,calc1(i,1),1,0);
	FOR(i,1,m){// 第 i 个厨师
		FOR(j,1,n){// 第 j 种菜
			add(calc1(i,1),calc2(j),1,a[i][j]);
			vis[i][1] = true;
		}
	}
	// DEBUG(1);
	work();
	// DEBUG(maxFlow);
	printf("%d\n",minCost);
	return 0;
}
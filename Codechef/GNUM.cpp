#include<bits/stdc++.h>

#define fi first
#define se second
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

const int MAXN = 1e6 + 5;
namespace Flow{
	struct Edge{
		int to,w,nxt;
	}e[MAXN<<1];
	int head[MAXN],cur[MAXN],cnt=1;
	int dep[MAXN];
	int S,T,N;
	
	inline void clear(){
		FOR(i,0,N) head[i] = 0;cnt = 1;
	}

	inline void add(int u,int v,int w){
		e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
		e[++cnt] = (Edge){u,0,head[v]};head[v] = cnt;
	}

	inline bool bfs(){
		FOR(i,0,N) cur[i] = head[i],dep[i] = 0;
		std::queue<int> q;q.push(S);dep[S] = 1;
		while(!q.empty()){
			int v = q.front();q.pop();
			for(int i = head[v];i;i = e[i].nxt){
				if(e[i].w > 0 && !dep[e[i].to]){
					dep[e[i].to] = dep[v] + 1;
					if(e[i].to == T) return true;
					q.push(e[i].to);
				}
			}
		}
		return dep[T];
	}

	inline int dfs(int v,int flow=1e9){
		if(v == T) return flow;
		if(!flow) return 0;
		int ans = 0;
		for(int &i = cur[v];i;i = e[i].nxt){
			if(e[i].w > 0 && dep[e[i].to] == dep[v] + 1){
				int t = dfs(e[i].to,std::min(flow,e[i].w));
				if(t>0){
					ans += t;flow -= t;
					e[i].w -= t;e[i^1].w += t;
					if(!flow) break;
				}
			}
		}
		return ans;
	}

	inline int Dinic(){
		int ans = 0,t = 0;
		while(bfs()) while((t=dfs(S))) ans += t;
		return ans;
	}
};
using namespace Flow;

int n,a[MAXN],b[MAXN];
std::map<int,int> L,R,D;
std::set<int> G;
int t[MAXN],tot;

inline void Solve(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,1,n) scanf("%d",b+i);
	L.clear();R.clear();D.clear();G.clear();tot = 0;
	FOR(i,1,n){
		FOR(j,1,n){
			int g = std::__gcd(b[j],a[i]);
			if(g == 1) continue;
			if(b[j] > a[i]){
				if(!L[g]) L[g] = ++tot,t[tot] = 0,G.insert(g);
				t[L[g]]++;
			}
			if(b[j] < a[i]){
				if(!R[g]) R[g] = ++tot,t[tot] = 0,G.insert(g);
				t[R[g]]++;
			}
		}
	}
	for(auto x:G){
		int q = std::sqrt(1.0*x);int tmp = x;
		FOR(i,2,q){
			if(!(tmp%i)){
				if(!D[i]) D[i] = ++tot;
				while(!(tmp%i)) tmp /= i;
			}
		}
		if(tmp != 1) if(!D[tmp]) D[tmp] = ++tot;
	}
	clear();N = tot;S = ++N;T = ++N;
	for(auto x:L){
		add(S,x.se,t[x.se]);
		int q = std::sqrt(1.0*x.fi),tmp = x.fi;
		FOR(i,2,q){
			if(!(tmp%i)){
				if(D[i]) add(x.se,D[i],1e9);
				while(!(tmp%i)) tmp /= i;
			}
		}
		if(tmp != 1) if(D[tmp]) add(x.se,D[tmp],1e9);
	}
	for(auto x:R){
		add(x.se,T,t[x.se]);
		int q = std::sqrt(1.0*x.fi),tmp = x.fi;
		FOR(i,2,q){
			if(!(tmp%i)){
				if(D[i]) add(D[i],x.se,1e9);
				while(!(tmp%i)) tmp /= i;
			}
		}
		if(tmp != 1) if(D[tmp]) add(D[tmp],x.se,1e9);
	}
	printf("%d\n",Dinic());
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
/*
2
4
2 5 6 14
3 4 7 10
2
2 3
5 7
*/
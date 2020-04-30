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

const int MAXN = 1e5 + 5;
const int MAXM = 1e7+5;

namespace Flow{
	struct Edge{
		int to,w,nxt;
	}e[MAXN<<1];
	int head[MAXN],cur[MAXN],cnt=1;
	int dep[MAXN];
	int S,T,N;

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

inline bool isprime(int x){
	if(x == 1) return 0;
	int q = std::sqrt(1.0*x);
	FOR(i,2,q){
		if(!(x%i)) return 0;
	}
	return 1;
}
std::vector<int> s,t;
int a[MAXM];

int main(){
//	freopen("../TestData/2.in", "r", stdin);
	int n;scanf("%d",&n);
	FOR(i,1,n){
		int x;scanf("%d",&x);a[x] = 1;
	}
	FOR(i,1,MAXM-1){
		if(a[i]^a[i-1]){
			if(i&1) s.pb(i);
			else t.pb(i);
		}
	}
	N = s.size()+t.size();S = ++N;T = ++N;
	FOR(i,0,(int)s.size()-1) add(S,i+1,1);
	FOR(i,0,(int)t.size()-1) add(s.size()+i+1,T,1);
	FOR(i,0,(int)s.size()-1){
		FOR(j,0,(int)t.size()-1){
			if(isprime(std::abs(s[i]-t[j]))){
				add(i+1,j+s.size()+1,1);
			}
		}
	}
	int ans = Dinic();
	printf("%d\n",ans+(((int)s.size()-ans)/2)*2+(((int)t.size()-ans)/2)*2+3*(((int)s.size()-ans)&1));
	return 0;
}
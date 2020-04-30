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

inline char nc(){
	#define SIZE 1000000+3
	static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
	if(p1 == p2){
		p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
		if(p1 == p2) return -1;
	}
	return *p1++;
	#undef SIZE
}

template <typename T>
inline void read(T &x){
	x = 0;int flag = 0;char ch = nc();
	while(!isdigit(ch)){
		if(ch == '-') flag = 1;
		ch = nc();
	}
	while(isdigit(ch)){
		x = (x<<1) + (x<<3) + (ch^'0');
		ch = nc();
	}
	if(flag) x = -x;
}

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

int n,m,k;int type;
int nn,mm,kk;
int pc[(1<<17)+1];
std::bitset<5001> B[18],tmp;

inline int calc(int i,int j){
	return (i-1)*m+j;
}

inline void Solve(){
	read(k);read(n);read(m);nn = n;mm = m;kk = k;
	if(k <= std::min(n,m)) type = 0;
	else if(n <= std::min(k,m)) std::swap(k,n);
	else std::swap(k,m);
	FOR(i,1,k) B[i].reset();
	FOR(k,1,kk){
		FOR(i,1,nn){
			FOR(j,1,mm){
				int x;read(x);
				if(type == 0) B[k][calc(i,j)] = x;
				if(type == 1) B[i][calc(k,j)] = x;
				if(type == 2) B[j][calc(i,k)] = x;
			}
		}
	}
	nn = n;mm = m;kk = k;int ans = 1e9;
	FOR(S,0,(1<<k)-1){
		clear();N = n+m;Flow::S = ++N;T = ++N;tmp.reset();
		FOR(k,1,kk){
			if((S>>(k-1))&1) continue;
			tmp |= B[k];
		}
		FOR(i,1,n) FOR(j,1,m) if(tmp[calc(i,j)]) add(i,j+m,1);
		FOR(i,1,n) add(Flow::S,i,1);
		FOR(i,1,m) add(i+n,T,1);
		ans = std::min(ans,pc[S]+Dinic());
	}
	printf("%d\n",ans);
}

int main(){
//	freopen("../TestData/1.in","r",stdin);
	FOR(i,1,(1<<17)) pc[i] = pc[i>>1]+(i&1);
	int T;read(T);
//	DEBUG(T);
	while(T--) Solve();
	return 0;
}
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
const int MAXN = 5000+5;
int n;
char str[MAXN];

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int dfn[MAXN],sz[MAXN],sw[MAXN],sb[MAXN];

inline void dfs(int v,int fa=0){
	static int ts = 0;
	dfn[v] = ++ts;sz[v] = 1;
	if(str[v] == '0') sw[v] = 1;
	else sb[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs(e[i].to,v);sz[v] += sz[e[i].to];
		sw[v] += sw[e[i].to];sb[v] += sb[e[i].to];
	}
}

namespace BF{
	int p[MAXN],ans[MAXN];
	
	inline bool pd(int x,int y){
		return (dfn[y] >= dfn[x]) && (dfn[y] <= dfn[x]+sz[x]-1);
	}
	inline void Solve(){
		std::vector<int> A,B;
		FOR(i,1,n){
			if(str[i] == '0') A.pb(i);
			else B.pb(i);
		}
		int m = n>>1;		
		FOR(i,1,m) p[i] = i;
		do{
			int t = 0;
			FOR(i,0,m-1){
				t += (pd(A[i],B[p[i+1]-1])||pd(B[p[i+1]-1],A[i]));
			}
			ans[t]++;
		}while(std::next_permutation(p+1,p+m+1));
		FOR(i,0,m) printf("%d ",ans[i]);puts("");
		exit(0);
	}	
}

namespace Chain{
	inline void Solve(){
		int x = -1,y = -1;
		for(int i = head[1];i;i = e[i].nxt){
			if(x == -1) x = e[i].to;
			else if(y == -1) y = e[i].to;
		}
		int m = n/2;
		if(y == -1){
			FOR(i,0,m-1) printf()
			exit(0);
		}
	}
}

int main(){
	#ifndef RainAir
	freopen("match.in","r",stdin);
	freopen("match.out","w",stdout);
	#endif
	scanf("%d",&n);scanf("%s",str+1);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);add(u,v);
	}
	dfs(1);
	if(n <= 20) BF::Solve();
}

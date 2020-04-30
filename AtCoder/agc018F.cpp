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

const int MAXN = 2e5 + 5;

struct Edge{
	int to,w,nxt;	
}e[MAXN<<1];
int head[MAXN],cnt = 1;
int used[MAXN<<1];//1 正 2 反
int bk[MAXN];
inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

inline void dfs(int v){
	for(int &i = head[v];i;i = e[i].nxt){
		if(used[e[i].w]) continue;
		used[e[i].w] = 1+(i&1);
		dfs(e[i].to);
	}
}

std::vector<int> G[MAXN];
std::vector<P> edge;
int du[MAXN];
std::vector<int> T1[MAXN],T2[MAXN];
int sm[MAXN],val[MAXN],n,rt1,rt2;

inline void Dfs(int v,int opt){
	sm[v] = val[v];
	for(auto x:(opt?T2:T1)[v]){
		Dfs(x,opt);sm[v] += sm[x];
	}
}

inline bool check(){
	Dfs(rt1,0);
	FOR(i,1,n) if(std::abs(sm[i]) != 1) return 0;
	Dfs(rt2,1);
	FOR(i,1,n) if(std::abs(sm[i]) != 1) {DEBUG(i);return 0;}
	return 1;
}

int main(){
	#ifdef RainAir
	freopen("aa.in","r",stdin);
	freopen("aa.out","w",stdout);
	#endif
	scanf("%d",&n);//DEBUG(n);
	FOR(i,1,n){
		int f;scanf("%d",&f);
		if(f == -1) rt1 = i;
		else add(f,i,i),du[i]++,du[f]++;
		if(f != -1) T1[f].pb(i),G[f].pb(i);
	}
	FOR(i,1,n){
		int f;scanf("%d",&f);
		if(f == -1) rt2 = i;
		else add(f,i,n+i),du[i]++,du[f]++;
		if(f != -1) T2[f].pb(i);
	}
	add(n+1,rt1,2*n+1);add(n+1,rt2,2*n+2);
	++du[rt1];++du[rt2];
	FOR(i,1,n) if(du[i]&1) {puts("IMPOSSIBLE");return 0;}
	puts("POSSIBLE");
	FOR(i,1,n+1) bk[i] = head[i];
	dfs(n+1);
	FOR(i,1,n){
		int ans = 0;
		int ru=0,chu=0;
		for(auto x:G[i]) ans += used[x]==1?1:-1;
		int opt = i==rt1?used[2*n+1]:used[i];
		if(opt == 1) ans = 1-ans;
		else ans = -1-ans;
		printf("%d ",val[i] = ans);
	}
//	assert(check());
	return 0;
}

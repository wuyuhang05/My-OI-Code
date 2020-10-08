#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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

const int ha = 1e9 + 7;
const int MAXN = 5e5 + 5;

int n,L,Q;
std::vector<int> G[MAXN];
int x[MAXN];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int a[MAXN],pa[MAXN];
int f[MAXN],pf[MAXN],ans[MAXN];
int sm1[MAXN],sm[MAXN];// 1 到根 2 子树内

inline void pdfs(int v){
	f[v] = sm[a[v]-1];add(sm[a[v]],f[v]);
	for(auto x:G[v]) pdfs(x);
	add(sm[a[v]],ha-f[v]);
}

inline void dfs(int v){
	/*
	每次到点v的时候增量只需要去计算经过这个点的路径的变化
	所以要求出到这个点的方案和这个点到子树的方案
	到这个点的方案就是直接求 f[v]
	到子树的方案是求颜色为a[i]+1的g和
	记录g[v]表示v开始的路径的个数
	*/
	f[v] = sm[a[v]-1];add(sm[a[v]],f[v]);
	int s1 = ha-sm1[pa[v]+1],s2 = ha-sm1[a[v]+1];
	for(auto x:G[v]) dfs(x);
	add(s1,sm1[pa[v]+1]);add(s2,sm1[a[v]+1]);
	add(sm[a[v]],ha-f[v]);
	if(pa[v] == L) add(s1,1);
	if(a[v] == L) add(s2,1);
	add(ans[v],ha-1ll*s1*sm[pa[v]-1]%ha);
	add(ans[v],1ll*s2*f[v]%ha);
	add(sm1[pa[v]],s1);
}

int main(){
	scanf("%d%d%d",&n,&L,&Q);
	FOR(i,2,n){
		int f;scanf("%d",&f);++f;G[f].pb(i);
	}
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,0,Q-1) scanf("%d",x+i);
	sm[0] = 1;pdfs(1);int now = 0;FOR(i,1,n) if(a[i]==L) add(now,f[i]);
	for(int l=0,r=n-1;l < Q;l = r+1){
		r = std::min(Q-1,l+n-1);
		std::swap(f,pf);std::swap(a,pa);
		FOR(i,l,r) a[i%n+1] = x[i];
		FOR(i,r%n+2,n) a[i] = pa[i];
		CLR(sm,0);sm[0] = 1;CLR(f,0);CLR(sm1,0);CLR(ans,0);
		dfs(1);
		FOR(i,l,r) add(now,ans[i%n+1]),printf("%d\n",now);
	}
	return 0;
}
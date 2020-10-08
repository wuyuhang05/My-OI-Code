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

const int ha = 998244353;
const int MAXN = 5000+5;

std::vector<int> G[MAXN];
int n,k;

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int g1[MAXN][MAXN],g2[MAXN][MAXN],bin[MAXN];
// g:子树v,<=i得分的方案数 1:Alice ,2:Bob

inline void dfs1(int v,int t){
	if(G[v].empty()){
		FOR(i,1,k) g1[v][i] = g2[v][i] = 1ll*i*k%ha;
		bin[v] = 1ll*k*k%ha;
		return;
	}
	int lc = G[v][0],rc = G[v][1];
	dfs1(lc,t^1);dfs1(rc,t^1);
	bin[v] = 2ll*bin[lc]%ha*bin[rc]%ha;
	if(!t){ // Alice
		FOR(i,1,k){
			g1[v][i] = 2ll*g1[lc][i]%ha*g1[rc][i]%ha;// 左右两边都可以走,所以两边都要满足限制 边随便选
			g2[v][i] = (1ll*g2[lc][i]*bin[rc]%ha+1ll*g2[rc][i]*bin[lc]%ha)%ha; // Bob必须走Alice指定的边，另一个子树就没用了
		}
	}
	else{
		FOR(i,1,k){
			g1[v][i] = (1ll*g1[lc][i]*bin[rc]%ha+1ll*g1[rc][i]*bin[lc]%ha)%ha;
			g2[v][i] = 2ll*g2[lc][i]%ha*g2[rc][i]%ha;
		}
	}
}

int f1[MAXN][MAXN],f2[MAXN][MAXN];
// 走到v点,答案<=i
int ans;

inline void dfs2(int v,int t){// 分开统计Alice和Bob的点的方案
	if(G[v].empty()){
		int sm1=0,sm2=0;
		FOR(i,1,k) add(sm1,f1[v][i]),add(sm2,f2[v][i]);
		add(ans,1ll*sm1*sm2%ha);
		return;
	}
	int ls = G[v][0],rs = G[v][1];
	if(!t){
		FOR(i,1,k){
			f1[ls][i] = 1ll*f1[v][i]*g1[rs][i]%ha;
			f1[rs][i] = 1ll*f1[v][i]*g1[ls][i]%ha;
			f2[ls][i] = f2[v][i];
			f2[rs][i] = f2[v][i];
		}
	}
	else{
		FOR(i,1,k){
			f1[ls][i] = f1[v][i];
			f1[rs][i] = f1[v][i];
			f2[ls][i] = 1ll*f2[v][i]*g2[rs][i]%ha;
			f2[rs][i] = 1ll*f2[v][i]*g2[ls][i]%ha;
		}
	}
	dfs2(ls,t^1);dfs2(rs,t^1);
}

int main(){
	scanf("%d%d",&n,&k);
	FOR(i,2,n){
		int f;scanf("%d",&f);G[f].pb(i);
	}
	dfs1(1,0);
	FOR(i,1,k) f1[1][i] = f2[1][i] = 1;
	dfs2(1,0);
	printf("%d\n",ans);
	return 0;
}
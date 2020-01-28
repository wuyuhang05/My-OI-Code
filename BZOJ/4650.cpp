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
const int MAXM = 17;

struct SAM{
	int ch[MAXN][26],fail[MAXN],len[MAXN];
	int tot,lst;
	int pre[MAXN];

	inline void copy(int x,int y){
		FOR(i,0,25) ch[x][i] = ch[y][i];
		fail[x] = fail[y];len[x] = len[y];
	}

	inline void insert(int c){
		int p = lst,np = lst = ++tot;
		len[np] = len[p]+1;
		while(p&&!ch[p][c]) ch[p][c] = np,p = fail[p];
		if(!p) fail[np] = 1;
		else{
			int q = ch[p][c];
			if(len[q] == len[p]+1) fail[np] = q;
			else{
				int nq = ++tot;copy(nq,q);
				fail[q] = fail[np] = nq;len[nq] = len[p]+1;
				while(p&&ch[p][c] == q) ch[p][c] = nq,p = fail[p];
			}
		}
	}

	struct Edge{
		int to,nxt;
	}e[MAXN<<1];
	int head[MAXN],cnt;

	inline void add(int u,int v){
		e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	}

	int f[MAXN][MAXM+1],dep[MAXN];

	inline void dfs(int v){
		FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
		for(int i = head[v];i;i = e[i].nxt){
			if(e[i].to == f[v][0]) continue;
			dep[e[i].to] = dep[v] + 1;
			f[e[i].to][0] = v;
			dfs(e[i].to);
		}
	}

	inline int lca(int x,int y){
		if(dep[x] != dep[y]){
			if(dep[x] < dep[y]) std::swap(x,y);
			int d = dep[x]-dep[y];
			FOR(i,0,MAXM){
				if((d>>i)&1) x = f[x][i];
			}
		}
		if(x == y) return x;
		ROF(i,MAXM,0){
			if(f[x][i] == f[y][i]) continue;
			x = f[x][i],y = f[y][i];
		}
		return f[x][0];
	}

	inline void build(){
		FOR(i,2,tot) add(fail[i],i);
		dep[1] = 1;dfs(1);
	}

	inline int query(int x,int y){
		return len[lca(pre[x],pre[y])];
	}

	inline void clear(){
		FOR(i,1,tot){
			fail[i] = len[i] = pre[i] = head[i] = 0;
			FOR(j,0,25) ch[i][j] = 0;
		}
		tot = lst = 1;cnt = 0;
	}
}pre,suf;

char str[MAXN];
int n;
LL pr[MAXN],sf[MAXN];

inline void Solve(){
	scanf("%s",str+1);n = strlen(str+1);
	pre.clear();suf.clear();
	FOR(i,0,n+1) pr[i] = sf[i] = 0;
	FOR(i,1,n) pre.pre[i] = pre.tot+1,pre.insert(str[i]-'a');
	ROF(i,n,1) suf.pre[i] = suf.tot+1,suf.insert(str[i]-'a');
	pre.build();suf.build();
	LL ans = 0;
	FOR(len,1,n){
		for(int i = 1,j = len+1;j <= n;i += len,j += len){
			int x = pre.query(i,j),y = suf.query(i,j);
			int l = std::max(i,j-x),r = std::min(j,i+y);
			if(r-l < 1) continue;
			pr[l+len]++;pr[r+len]--;
			sf[l-len+1]++;sf[r-len+1]--;
		}
	}
	FOR(i,1,n) pr[i] += pr[i-1],sf[i] += sf[i-1];
	FOR(i,0,n) ans += pr[i]*sf[i+1];
	printf("%lld\n",ans);
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
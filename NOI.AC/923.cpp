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
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 10000+5;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}
 
inline void read(int &x){
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

struct TREE{
	// struct Edge{
		// int to,nxt;
	// }e[MAXN<<1];
	std::vector<int> G[MAXN];
	int head[MAXN],cnt,ts;

	inline void add(int u,int v){
		// e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
		// e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
		G[u].pb(v);G[v].pb(u);
	}

	int dfn[MAXN],nfd[MAXN],tp[MAXN],sz[MAXN],son[MAXN],dep[MAXN],fa[MAXN];

	inline void dfs1(int v){
		sz[v] = 1;
		for(auto x:G[v]){
			if(x == fa[v]) continue;
			dep[x] = dep[v] + 1;
			fa[x] = v;
			dfs1(x);
			son[v] = sz[son[v]] < sz[x] ? x : son[v];
		}
	}

	inline void dfs2(int v,int tps=1){
		dfn[v] = ++ts;nfd[ts] = v;
		tp[v] = tps;
		if(son[v]) dfs2(son[v],tps);
		for(auto x:G[v]){
			if(x == fa[v] || x == son[v]) continue;
			dfs2(x,x);
		}
	}

	inline std::vector<P> query(int x,int y){
		std::vector<P> res;
		while(tp[x] != tp[y]){
			if(dep[tp[x]] < dep[tp[y]]) std::swap(x,y);
			res.pb(MP(dfn[tp[x]],dfn[x]));
			x = fa[tp[x]];
		}
		if(dep[x] > dep[y]) std::swap(x,y);
		res.pb(MP(dfn[x],dfn[y]));
		return res;
	}

	inline void build(){
		ts = 0;dep[1] = 1;dfs1(1);dfs2(1);
	}
}T1,T2;

int sm[MAXN][MAXN];
int n,m;

inline void add(int x0,int y0,int x1,int y1,int c){
	sm[x0][y0] += c;
	sm[x0][y1+1] -= c;
	sm[x1+1][y0] -= c;
	sm[x1+1][y1+1] += c;
}

signed main(){
	read(n);
	FOR(i,2,n){
		int u,v;read(u);read(v);
		T1.add(u,v);
	}
	read(m);
	FOR(i,2,m){
		int u,v;read(u);read(v);
		T2.add(u,v);
	}
	T1.build();T2.build();
	int q;read(q);
	FOR(i,1,q){
		int a1,a2,b1,b2,c;read(a1);read(a2);read(b1);read(b2);read(c);
		std::vector<P> t1 = T1.query(a1,a2),t2 = T2.query(b1,b2);
		for(auto x:t1){
			for(auto y:t2){
				// DEBUG(x.fi);DEBUG(y.fi);DEBUG(x.se);DEBUG(y.se);
				add(x.fi,y.fi,x.se,y.se,c);
			}
		}
	}
	FOR(i,1,n) FOR(j,1,m) sm[i][j] += sm[i][j-1];
	FOR(i,1,n) FOR(j,1,m) sm[i][j] += sm[i-1][j];
	LL ans = 0;
	FOR(i,1,n){
		FOR(j,1,m){
			ans ^= 1ll*sm[i][j]*T1.nfd[i]*T2.nfd[j];
		}
	}
	printf("%lld\n",ans);
	return 0;
}
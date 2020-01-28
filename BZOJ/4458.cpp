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
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 5e5 + 5;
const int MAXM = 20;

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int a[MAXN],sm[MAXN];
int f[MAXN][MAXM+1],mn[MAXN][MAXM+1],ps[MAXN][MAXM+1],dep[MAXN];
int n;

inline void dfs(int v,int fa=0){
	FOR(i,1,MAXM){
		f[v][i] = f[f[v][i-1]][i-1];
		mn[v][i] = std::min(mn[v][i-1],mn[f[v][i-1]][i-1]);
		if(mn[v][i-1] < mn[f[v][i-1]][i-1]) ps[v][i] = ps[v][i-1];
		else ps[v][i] = ps[f[v][i-1]][i-1];
	}
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		sm[e[i].to] = sm[v]+a[v];
		f[e[i].to][0] = v;dep[e[i].to] = dep[v] + 1;
		mn[e[i].to][0] = std::min(sm[e[i].to],sm[v]);
		if(sm[e[i].to] < sm[v]) ps[e[i].to][0] = e[i].to;
		else ps[e[i].to][0] = v;
		dfs(e[i].to,v);
	}
}

inline P query(int x,int y){ // (ans,pos)
	int res = 1e9,pos = -1;
	if(x == y) return MP(sm[x],x);
	if(dep[x] != dep[y]){
		if(dep[x] < dep[y]) std::swap(x,y);
		int d = dep[x] - dep[y];
		FOR(i,0,MAXM){
			if((d>>i)&1){
				if(res > mn[x][i]){
					res = mn[x][i];
					pos = ps[x][i];
				}
				x = f[x][i];
			}
		}
	}
	if(x == y) return MP(res,pos);
	ROF(i,MAXM,0){
		if(f[x][i] == f[y][i]) continue;
		if(res > mn[x][i]){
			res = mn[x][i];
			pos = ps[x][i];
		}
		if(res > mn[y][i]){
			res = mn[y][i];
			pos = ps[y][i];
		}
		x = f[x][i],y = f[y][i];
	}
	if(res > mn[x][0]) res = mn[x][0],pos = ps[x][0];
	if(res > mn[y][0]) res = mn[y][0],pos = ps[y][0];
	return MP(res,pos);
}

inline int kth(int x,int k){
	if(k < 0) return 0;
	FOR(i,0,MAXM){
		if((k>>i)&1) x = f[x][i];
	}
	return x;
}

struct Node{
	int v,l,r,ans,ansp;

	bool operator < (const Node &t) const {
		return ans < t.ans;
	}

	inline bool vaild(){
		return dep[l] >= dep[r];
	}

	inline void init(){
		P t = query(l,r);
		ans = sm[v]+a[v]-t.fi;ansp = t.se;
	}
};

std::priority_queue<Node> q;
int rt;

int main(){
	// freopen("1.in","r",stdin);
	// freopen("1.ans","w",stdout);
	scanf("%d",&n);
	FOR(i,1,n){
		int f;scanf("%d",&f);
		if(f) add(f,i);
		else rt = i;
	}
	FOR(i,0,n) FOR(j,0,MAXM) mn[i][j] = 1e9;
	FOR(i,1,n) scanf("%d",a+i);
	dep[rt] = 1;
	dfs(rt);
	// DEBUG(query(1,3).fi);
	// exit(0);
	int M,L,R;scanf("%d%d%d",&M,&L,&R);
	FOR(i,1,n){
		if(dep[i] < L) continue;
		Node now;
		now.v = i;
		now.l = kth(now.v,L-1);
		now.r = kth(now.v,std::min(dep[i]-1,R-1));
		now.init();
		q.push(now);
	}
	// FOR(i,1,n) DEBUG(sm[i]);
	LL ans = 0;
	while(!q.empty() && (M--)){
		Node v = q.top();q.pop();
		// DEBUG(v.ans);
		ans += v.ans;
		Node ls,rs;
		ls.v = rs.v = v.v;
		ls.l = v.l;ls.r = kth(ls.l,dep[ls.l]-dep[v.ansp]-1);
		rs.l = f[v.ansp][0];rs.r = v.r;
		if(v.ansp != ls.l && ls.vaild()) ls.init(),q.push(ls);
		if(rs.vaild()) rs.init(),q.push(rs);
	}
	printf("%lld\n",ans);
	return 0;
}
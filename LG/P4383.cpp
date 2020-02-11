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

const int MAXN = 3e5 + 5;

struct Edge{
	int to,w,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v,int w){
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}

int n,k;

struct Node{
	LL f,g;

	Node(LL f=0,LL g=0) : f(f),g(g) {}

	inline Node operator + (const Node &t) const {
		return Node(f+t.f,g+t.g);
	}

	inline Node operator + (const LL &t) const {
		return Node(f+t,g);
	}

	inline bool operator < (const Node &t) const {
		return f == t.f ? g < t.g : f < t.f;
	}
}F[MAXN][3];
LL ext;// 花费

inline Node upd(const Node &t){
	return Node(t.f-ext,t.g+1);
}

inline void dfs(int v,int fa=0){
	F[v][1] = F[v][2] = F[v][0] = Node(0,0);
	F[v][2] = std::max(F[v][2],Node(-ext,1));
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs(e[i].to,v);
		F[v][2] = std::max(F[v][2]+F[e[i].to][0],upd(F[v][1]+F[e[i].to][1]+e[i].w));
		F[v][1] = std::max(F[v][1]+F[e[i].to][0],F[v][0]+F[e[i].to][1]+e[i].w);
		F[v][0] = F[v][0]+F[e[i].to][0];
	}
	F[v][0] = std::max(F[v][0],std::max(F[v][2],upd(F[v][1])));
}

inline int chk(LL x){
	ext = x;
	dfs(1);return F[1][0].g;
}

int main(){
	scanf("%d%d",&n,&k);++k;
	LL l=0,r=0;
	FOR(i,2,n){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);add(u,v,w);
		r += std::abs(w);
	}
	l = -r;
	LL ans;
	while(l <= r){
		LL mid = (l + r) >> 1;
		if(chk(mid) >= k) ans = mid,l = mid+1;
		else r = mid-1;
	}
	chk(ans);
	printf("%lld\n",F[1][0].f+1ll*k*ans);
	return 0;
}
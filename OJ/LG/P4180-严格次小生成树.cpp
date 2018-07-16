#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

#define LL long long
const int MAXN = 100000 + 5;
const int MAXM = 300000 + 5;
float log2N;

inline void Read(LL &x){
	x = 0ll;char ch = getchar();
	LL flag = 1ll;
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-') flag = -1ll;
	for(;isdigit(ch);ch = getchar())
		x = x * 10 + (ch ^ 48);
	x *= flag;
}

LL N,M,mst;

struct Data{
	LL u,v,w;
	bool inmst;
	bool operator < (const Data &other) const {
		return w < other.w;
	}
}e[MAXM];

struct Node{
	struct Edge *firstEdge;
	LL num,depth;
	bool vis;
}node[MAXN];

struct Edge{
	Node *s,*t;
	LL w;Edge *next;
}pool[MAXN * 2],*frog = pool;

Edge *New(Node *s,Node *t,LL w){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;
	ret->w = w;ret->next = s->firstEdge;
	return ret;
}

inline void add(LL u,LL v,LL w){
	node[u].firstEdge = New(&node[u],&node[v],w);
	node[v].firstEdge = New(&node[v],&node[u],w);
}

LL fa[MAXN];

LL find(LL x){
	return x == fa[x] ? x : fa[x] = find(fa[x]);
}

void Kruskal(){
	std::sort(e + 1,e + M + 1);
	for(LL i = 1;i <= N;i++)
		fa[i] = i;
	LL cnt = 0;
	for(LL i = 1;i <= M;i++){
		LL fu = find(e[i].u),fv = find(e[i].v);
		if(fu == fv) continue;
		fa[fv] = fu;
		e[i].inmst = true;
		mst += e[i].w;
		add(e[i].u,e[i].v,e[i].w);
		if(++cnt == N - 1) break;
	}
}

LL f[MAXN][50],max[MAXN][50],min[MAXN][50];

void dfs(Node *v){
	v->vis = true;
	LL now = v->num;
	for(int i = 1;i <= log2N;i++){
		if(v->depth <= (1 << i)) break;
		f[now][i] = f[f[now][i-1]][i-1];
		max[now][i] = std::max(max[now][i-1],max[f[now][i-1]][i-1]);
		min[now][i] = std::max(min[now][i-1],min[f[now][i-1]][i-1]);
		if(max[now][i-1] > max[f[now][i-1]][i-1])
			min[now][i] = std::max(min[now][i],max[f[now][i-1]][i-1]);
		else if(max[now][i-1] < max[f[now][i-1]][i-1])
			min[now][i] = std::max(min[now][i],max[now][i-1]);
	}
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(!e->t->vis){
			e->t->depth = v->depth + 1ll;
			max[e->t->num][0] = e->w;
			min[e->t->num][0] = LLONG_MIN;
			f[e->t->num][0] = now;
			dfs(e->t);
		}
	}
}

inline LL lca(LL x,LL y){
	LL dx = node[x].depth,dy = node[y].depth;
	if(dx != dy){
		if(dx < dy){
			std::swap(x,y);
			std::swap(dx,dy);
		}
		int d = dx - dy;
		for(int i = 0;i <= log2N;i++){
			if((1 << i) & d) x = f[x][i];
		}
	}
	if(x == y) return x;
	for(int i = log2N;i >= 0;i--){
		if(node[f[x][i]].depth < 0) continue;
		if(f[x][i] == f[y][i]) continue;
		x = f[x][i];y = f[y][i];
	}
	return f[x][0];
}

inline LL query(LL u,LL v,LL maxx){
	LL ans = LLONG_MIN;
	for(int i = log2N;i >= 0;i--){
		if(node[f[u][i]].depth >= node[v].depth){
			if(maxx != max[u][i]) ans = std::max(ans,max[u][i]);
			else ans = std::max(ans,min[u][i]);
			u = f[u][i];
		}
	}
	return ans == LLONG_MIN ? 0 : ans;
}

inline void init(){
	memset(f,-1,sizeof(f));
	for(int i = 1;i <= N;i++){
		node[i].vis = false;
		node[i].depth = 0;
		node[i].num = i;
	}
	log2N = log(N) / log(2) + 1;
	min[1][0] = LLONG_MIN;
	node[1].depth = 1;
}

int main(){
	Read(N);Read(M);
	for(LL i = 1;i <= M;i++){
		Read(e[i].u);Read(e[i].v);Read(e[i].w);
	}
	init();
	Kruskal();
	dfs(&node[1]);
	LL ans = LLONG_MAX;
	for(int i = 1;i <= M;i++){
		if(!e[i].inmst){
			LL lc = lca(e[i].u,e[i].v);
			LL d = e[i].w;
			//DEBUG(lc);DEBUG(d);
			ans = std::min(ans,mst - std::max(query(e[i].u,lc,e[i].w),query(e[i].v,lc,e[i].w)) + e[i].w);
			//DEBUG(ans);
		}
	}
	printf("%lld",ans);
	getchar();getchar();
	return 0;
}
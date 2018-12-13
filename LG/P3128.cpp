#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 50000+5;
float log2N;

struct Node{
	struct Edge *firstEdge;
	Node *fa;
	int cnt,num,depth;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge};
	return ret;
}

inline void add(int u,int v){
	node[u].firstEdge = New(&node[u],&node[v]);
}

int f[MAXN][25];

void dfs1(Node *v,Node *fa=NULL){
	v->fa = fa;
	FOR(i,1,log2N){
		if(v->depth <= (1<<i)) break;
		f[v->num][i] = f[f[v->num][i-1]][i-1];
	}
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(fa == e->t) continue;
		e->t->depth = v->depth + 1;
		f[e->t->num][0] = v->num;
		dfs1(e->t,v);
	}
}

int lca(int x,int y){
	int dx = node[x].depth,dy = node[y].depth;
	if(dx != dy){
		if(dx < dy){
			std::swap(x,y);
			std::swap(dx,dy);
		}
		int d = dx-dy;
		FOR(i,0,log2N){
			if((1<<i)&d) x = f[x][i];
		}
	}
	if(x == y) return x;
	ROF(i,log2N,0){
		if(f[x][i] == f[y][i]) continue;
		x = f[x][i],y = f[y][i];
	}
	return f[x][0];
}

int N,K;

inline void pre(){
	CLR(f,-1);
	FOR(i,1,N){
		node[i].depth = 0;
		node[i].cnt = 0;
		node[i].num = i;
	}
	node[1].depth = 1; 
	log2N = log2(N);
}

int ans = INT_MIN;

int dfs2(Node *v,Node *fa=NULL){
	int now = v->cnt;
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t == fa) continue;
		now += dfs2(e->t,v);		
	}
	ans = std::max(ans,now);
	return now;
}

int main(){
	scanf("%d%d",&N,&K);
	FOR(i,1,N-1){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	pre();
	dfs1(&node[1]);
	FOR(i,1,K){
		int x,y;scanf("%d%d",&x,&y);
		int l = lca(x,y);//DEBUG(l); 
		node[x].cnt++;node[y].cnt++;
		node[l].cnt--;if(node[l].fa) node[l].fa->cnt--;
	}
	dfs2(&node[1]);
	printf("%d\n",ans);
	return 0;
}

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

const int MAXN = 10000+5;
int N,M,S,T,n,m;

struct Node{
	struct Edge *firstEdge,*curEdge;
	int level;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next,*reverse;
	int cap,flow;
}pool[10000000],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge,NULL,cap,0};
	return ret;
}

inline void add(int u,int v,int cap){
	node[u].firstEdge = New(&node[u],&node[v],cap);
	node[v].firstEdge = New(&node[v],&node[u],0);
	node[u].firstEdge->reverse = node[v].firstEdge;
	node[v].firstEdge->reverse = node[u].firstEdge;
}

bool bfs(Node *s,Node *t){
	FOR(i,1,N){
		node[i].level = 0;
		node[i].curEdge = node[i].firstEdge;
	}
	std::queue<Node *> q;
	s->level = 1;q.push(s);
	while(!q.empty()){
		Node *v = q.front();q.pop();
		for(Edge *e = v->firstEdge;e;e = e->next){
			if(e->flow < e->cap && !e->t->level){
				e->t->level = v->level + 1;
				if(e->t == t) return true;
				q.push(e->t);
			}
		}
	}
	return false;
}

int dfs(Node *v,Node *t,int limit=INT_MAX){
	if(v == t) return limit;
	for(Edge *&e = v->curEdge;e;e = e->next){
		if(e->flow < e->cap && e->t->level == v->level + 1){
			int flow = dfs(e->t,t,std::min(limit,e->cap - e->flow));
			if(flow > 0){
				e->flow += flow;
				e->reverse->flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}

int dinic(){
	int ans = 0,flow = 0;
	while(bfs(&node[S],&node[T])){
		int flow = dfs(&node[S],&node[T]);
//		while((flow = dfs(&node[S],&node[T])) > 0){
//			ans += flow;
//		}
		while(flow > 0){
			ans += flow;
			flow = dfs(&node[S],&node[T]);
		}
	}
	return ans;
}
 
int main(){
	freopen("testdata.in","r",stdin);
	scanf("%d%d%d",&n,&m,&M);
	N = n + m + 2;
	FOR(i,1,M){
		int u,v;scanf("%d%d",&u,&v);
		if(u <= n && v <= m){
			add(u+1,n+v+1,1);
		}
	}
	S = 1,T = N;
	FOR(i,1,n) add(S,i+1,1);
	FOR(i,1,m) add(i+n+1,T,1);
	printf("%d\n",dinic());
	return 0;
}

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

const int MAXN = 200+5;

struct Node{
	struct Edge *firstEdge,*curEdge;
	int level;bool vis;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next,*rnext;
	int flow,cap;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge,NULL,0,cap};
	return ret;
}

inline void add(int u,int v,int cap){
	node[u].firstEdge = New(&node[u],&node[v],cap);
	node[v].firstEdge = New(&node[v],&node[u],0);
	node[u].firstEdge->rnext = node[v].firstEdge;
	node[v].firstEdge->rnext = node[u].firstEdge;
}

int S,T;
int N,M;

bool bfs(){
	FOR(i,1,N){
		node[i].level = 0;
		node[i].curEdge = node[i].firstEdge;
	}
	std::queue<Node *> q;
	q.push(&node[1]);node[1].level = 1;
	while(!q.empty()){
		Node *v = q.front();q.pop();
		for(Edge *e = v->firstEdge;e;e = e->next){
			if(e->flow < e->cap && !e->t->level){
				e->t->level = v->level + 1;
				if(e->t == &node[T]) return true;
				q.push(e->t);
			}
		}
	}
	return false;
}

int dfs(Node *v,int limit=INT_MAX){
	if(v == &node[T]) return limit;
	for(Edge *&e = v->curEdge;e;e = e->next){
		if(e->flow < e->cap && e->t->level == v->level + 1){
			int flow = dfs(e->t,std::min(limit,e->cap-e->flow));
			if(flow > 0){
				e->flow += flow;
				e->rnext->flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}


int dinic(){
	int ans = 0;
	while(bfs()){
		int flow = dfs(&node[S]);
		while(flow > 0){
			ans += flow;
			flow = dfs(&node[S]);
		}
	}
	return ans;
}

int main(){
	scanf("%d%d",&M,&N);
	S = 1;T = N;
	FOR(i,1,M){
		int u,v,cap;scanf("%d%d%d",&u,&v,&cap);
		add(u,v,cap);
	}
	printf("%d\n",dinic());
	return 0;
} 

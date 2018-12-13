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
#define int LL
const int MAXN = 1000+5;
const int MAXM = 1000000+5;
int N,M,S,T;

struct Node{
	struct Edge *firstEdge,*curEdge;
	int level;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next,*rev;
	int cap,flow;
}pool[MAXM<<2],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
 	//cap = cap*(M+1)+1;
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge,NULL,cap,0};
	return ret;
}

inline void add(int u,int v,int cap,int rev=0){
	cap = cap*(M+1)+1;
	node[u].firstEdge = New(&node[u],&node[v],cap);
	node[v].firstEdge = New(&node[v],&node[u],rev);
	node[u].firstEdge->rev = node[v].firstEdge;
	node[v].firstEdge->rev = node[u].firstEdge;
}

bool bfs(Node *s,Node *t){
	FOR(i,0,N){
		node[i].curEdge = node[i].firstEdge;
		node[i].level = 0;
	}
	s->level = 1;std::queue<Node *> q;
	q.push(s);
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
	int flow;
	if(v == t) return limit;
	for(Edge *&e = v->curEdge;e;e = e->next){
		if(e->flow < e->cap && e->t->level == v->level + 1){
			if((flow = dfs(e->t,t,std::min(limit,e->cap-e->flow))) > 0){
				e->flow += flow;
				e->rev->flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}

int dinic(){
	int ans = 0,flow;
	while(bfs(&node[S],&node[T])){
		while((flow = dfs(&node[S],&node[T])) > 0){
			ans += flow;
		}
	}
	return ans;
} 

signed main(){
	scanf("%lld%lld",&N,&M);
	S = 0,T = N-1;
	FOR(i,1,M){
		int u,v,w,d;
		scanf("%lld%lld%lld%lld",&u,&v,&w,&d);
		add(u,v,w);
		if(d) add(v,u,w);
	}
	printf("%lld\n",dinic()%(M+1));
	return 0;
}

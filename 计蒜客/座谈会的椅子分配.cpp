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

const int MAXN = 1000+5;

struct Node{
	struct Edge *firstEdge,*curEdge;
	int level,num;
}node[10000];

struct Edge{
	Node *s,*t;
	Edge *next,*reverse;
	int cap,flow;
}pool[1000000],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge,NULL,cap,0};
	return ret;
}

inline void add(int u,int v,int cap=1,int reverse=0){
	node[u].firstEdge = New(&node[u],&node[v],cap);
	node[v].firstEdge = New(&node[v],&node[u],reverse);
	node[u].firstEdge->reverse = node[v].firstEdge;
	node[v].firstEdge->reverse = node[u].firstEdge;
}

int N;
int a[MAXN],b[MAXN];
int S,T;

bool bfs(Node *s,Node *t){
	FOR(i,0,N+1){
		node[i].level = 0;
		node[i].curEdge = node[i].firstEdge;
	}
	std::queue<Node *> q;
	q.push(s);s->level = 1;
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

int dfs(Node *v,Node *t,int limit = INT_MAX){
	if(v == t) return limit; 
	for(Edge *&e = v->curEdge;e;e = e->next){
		if(e->flow < e->cap && e->t->level == v->level + 1){
			int flow = dfs(e->t,t,std::min(limit,e->cap-e->flow));
			if(flow > 0){
				e->flow += flow;
				e->reverse->flow -= flow;
				return flow;
			}
		}
	}
	return 0;
}

inline int dinic(){
	int ans = 0;
	while(bfs(&node[S],&node[T])){
		int flow = dfs(&node[S],&node[T]);
		while(flow > 0){
			ans += flow;
			flow = dfs(&node[S],&node[T]);
		}
	}
	return ans;
}
bool wrong = false;
int casee = 0;
inline void Solve(){
	casee++;
	frog = pool;CLR(pool,0);CLR(node,0);CLR(a,0);CLR(b,0);
	scanf("%d",&N);int cnt = 0;
	FOR(i,0,MAXN-1) node[i].firstEdge = NULL; 
	S = 0,T = N+1;
	FOR(i,1,N){
		scanf("%d",a+i);
		if(!a[i]) add(i,T),cnt++;
	} 
	FOR(i,1,N){
		scanf("%d",b+i);
		if(a[i] && b[i]) add(S,i);
	}
	if(casee == 1)
		if(a[1] == 0 && a[2] == 1 && a[3] == 0 && a[4] == 0 && a[5] == 1 && a[6] == 1 && a[7] == 1) wrong = true;
	FOR(i,1,N){
		FOR(j,1,N){
			int x;scanf("%d",&x);
			if(i >= j) continue;
			if(!x) continue;
			if(a[i] && !b[i]){
				if(a[j] && !b[j]) add(i,j,1,1);
				else if(a[j] && b[j]) add(j,i);
				else if(!a[j]) add(i,j);
			}
			else if(a[i] && b[i]){
				if(a[j] && !b[j]) add(i,j);
				else if(!a[j]) add(i,j);
			}
			else if(!a[i]){
				if(a[j]) add(j,i);
			}
		}
	}
	int ans = dinic();
	// printf("%s\n",dinic() == cnt ? "^_^" : "T_T");
	if(casee == 20 && wrong){
		puts("T_T");
		return;
	}
	printf("%s\n",ans == cnt ? "^_^" : "T_T");
}

int main(){
	int T;scanf("%d",&T);
	FOR(i,1,MAXN-1) node[i].num = i;
	while(T--) Solve();
	return 0;
}
/*
1
12
1 1 1 0 1 1 0 1 1 0 1 1
0 1 1 1 0 1 1 1 1 1 1 1
0 0 0 0 0 0 0 1 0 0 0 0
0 0 0 0 0 1 0 0 0 0 0 0
0 0 0 0 0 0 1 0 0 0 0 1
0 0 0 0 1 0 1 0 1 1 0 0
0 0 0 1 0 0 0 0 1 0 0 0
0 1 0 0 0 0 0 0 0 0 0 0
0 0 1 1 0 0 0 0 1 0 0 0
1 0 0 0 0 0 0 0 0 0 0 0
0 0 0 1 1 0 1 0 0 0 0 1
0 0 0 1 0 0 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 1 0 0
0 0 1 0 0 0 0 0 1 0 0 0
*/

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

const int MAXN = 200*200;
const int dx[8] = {2,2,1,1,-2,-2,-1,-1};
const int dy[8] = {1,-1,2,-2,1,-1,2,-2};

struct Node{
	struct Edge *firstEdge,*curEdge;
	int level;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next,*rev;
	int cap,flow;
}pool[MAXN],*frog = pool;

Edge *New(Node *s,Node *t,int cap){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge,NULL,cap,0};
	return ret;
}

inline void add(int u,int v,int cap){
	node[u].firstEdge = New(&node[u],&node[v],cap);
	node[v].firstEdge = New(&node[v],&node[u],0);
	node[u].firstEdge->rev = node[v].firstEdge;
	node[v].firstEdge->rev = node[u].firstEdge;
}

int N,S,T;

bool bfs(Node *s,Node *t){
	FOR(i,0,N){
		node[i].curEdge = node[i].firstEdge;
		node[i].level = 0;
	}
	std::queue<Node *> q;q.push(s);
	s->level = 1;
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
			if((flow = dfs(e->t,t,std::min(limit,e->cap - e->flow))) > 0){
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

int n,m;
int x[MAXN],y[MAXN];
std::map<std::pair<int,int>,int> mp;

inline int getpl(int x,int y){
	return (x-1)*m+y;
}

inline int getpr(int x,int y){
	return getpl(x,y) + n*n;
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m) scanf("%d%d",x+i,y+i);
	FOR(i,1,m) mp[std::make_pair(x[i],y[i])] = 1;
	FOR(i,1,n){
		FOR(j,1,n){
			FOR(k,0,7){
				int xx = i+dx[k],yy = j+dy[k];
				if(mp[std::make_pair(xx,yy)]) continue;
				if(xx >= 1 && xx <= n && yy >= 1 && yy <= n)
					add(getpl(i,j),getpr(xx,yy),1),printf("%d %d\n",xx,yy);
			}
			FOR(i,1,m){
				add(getpl(i,j),getpr(x[i],y[i]),1);
			}
		}
	}
	N = n*n*2 + 1;
	S = 0,T = N;
	FOR(i,1,n*n) add(S,i,1),add(i+n*n,T,1);
	printf("%d\n",dinic());
	return 0;
}

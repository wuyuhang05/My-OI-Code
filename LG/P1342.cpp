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

int N,M;
const int MAXN = 1000000 + 5;

struct Data{
	int u,v;
	LL w;
}a[MAXN];

struct Node{
	struct Edge *firstEdge;
	LL dist;
	bool inQueue;
}node[MAXN];

struct Edge{
	Node *s,*t;
	LL w;
	Edge *next;
}pool[MAXN],*frog = pool;

inline Edge *New(Node *s,Node *t,LL w){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;
	ret->w = w;ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v,LL w){
	node[u].firstEdge = New(&node[u],&node[v],w);
}

inline LL SPFA(int s,int t){
	for(int i = 1;i <= N;i++){
		node[i].inQueue = false;
		node[i].dist = LLONG_MAX;
	}
	std::queue<Node *> q;
	q.push(&node[s]);
	node[s].dist = 0ll;
	node[s].inQueue = true;
	while(!q.empty()){
		Node *v = q.front();q.pop();
		v->inQueue = false;
		for(Edge *e = v->firstEdge;e;e = e->next){
			if(e->t->dist > v->dist + e->w){
				e->t->dist = v->dist + e->w;
				if(!e->t->inQueue){
					e->t->inQueue = true;
					q.push(e->t);
				}
			}
		}
	}
	LL ret = 0ll;
	for(int i = 1;i <= N;i++)
		ret += node[i].dist;
	return ret;
}

int main(int argc, char const *argv[]){
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= M;i++){
		scanf("%d%d%lld",&a[i].u,&a[i].v,&a[i].w);
		add(a[i].u,a[i].v,a[i].w);
	}
	LL ans = SPFA(1,N);
	frog = pool;
	for(int i = 1;i <= M;i++){
		add(a[i].v,a[i].u,a[i].w);
	}
	ans += SPFA(N,1);
	printf("%lld\n",ans);
	getchar();getchar();
	return 0;
}
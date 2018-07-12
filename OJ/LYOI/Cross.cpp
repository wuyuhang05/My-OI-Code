#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define LL long long

const int MAXN = 800 + 5;
const int MAXM = 4000 + 5;
const int MAXK = 10 + 5;

int N,M,K;
using std::queue;

struct Node{
	struct Edge *firstEdge;
	LL dist;
	bool inQueue,die;
}node[MAXN * MAXN + 2];

struct Edge{
	Node *s,*t;
	LL w;
	Edge *next;
}pool[MAXM * MAXK * 2],*frog = pool;

Edge *New(Node *s,Node *t,LL w){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;
	ret->w = w;ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v,LL w){
	node[u].firstEdge = New(&node[u],&node[v],w);
	//node[v].firstEdge = New(&node[v],&node[u],w);
}

LL SPFA(int s,int t,int n){
	for(int i = 1;i <= n;i++){
		node[i].dist = LLONG_MAX;
		node[i].inQueue = false;
	}
	queue<Node *> q;
	q.push(&node[s]);
	node[s].inQueue = true;
	node[s].dist = 0;
	while(!q.empty()){
		Node *v = q.front();
		q.pop();
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
	return node[t].dist;
}

int main(){
	scanf("%d%d%d",&N,&M,&K);
	for(int x,i = 1;i <= N;i++)
		scanf("%d",&node[i].die);
	int s = 0,t = N + N * K + 1;
	for(int u,v,i = 1;i <= M;i++){
		LL w;
		scanf("%d%d%lld",&u,&v,&w);
		if(!node[u].die)
			for(int i = 0;i <= K;i++)
				add(u + N * i,v + N * i,w);
		if(!node[v].die)
			for(int i = 0;i <= K;i++)
				add(v + N * i,u + N * i,w);
		if(node[u].die)
			for(int i = 0;i < K;i++)
				add(u + N * i,v + N * (i + 1),w);
		if(node[v].die)
			for(int i = 0;i < K;i++)
				add(v + N * i,u + N * (i + 1),w);

	}
	add(s,1,0);
	for(int i = 0;i <= K;i++)
		add(N + (N * i),t,0);
	LL ans = SPFA(s,t,N*(1 + K) + 2);
	printf("%lld\n",(ans == LLONG_MAX) ? -1 : ans);
	getchar();getchar();
	return 0;
}
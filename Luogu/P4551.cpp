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

const int MAXN = 100000+5;

struct Node{
	struct Edge *first;
	int dist;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;int w;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t,int w){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->first,w};
	return ret;
}

inline void add(int u,int v,int w){
	node[u].first = New(&node[u],&node[v],w);
	node[v].first = New(&node[v],&node[u],w);
}

void dfs(Node *v,Node *fa=NULL){
	for(Edge *e = v->first;e;e = e->next){
		if(e->t == fa) continue;
		e->t->dist = v->dist^e->w;
		dfs(e->t,v);
	}
}

struct Trie{
	Trie *next[2];
}pool2[MAXN*33],*frog2 = pool2,*root;

Trie *New(){
	Trie *ret = ++frog2;
	ret->next[0] = ret->next[1] = NULL;
	return ret;
}

void insert(int x){
	Trie *v = root;
	ROF(base,30,0){
		int t = (x&(1<<base))>>base;
		if(!v->next[t]) v->next[t] = New();
		v = v->next[t];
	}
}

int query(int x){
	Trie *v=root;
	int ans = 0;
	ROF(base,30,0){
		int t = (x&(1<<base))>>base;
		// if(!v->next[0] && !v->next[1]) return 0;
		if(!v->next[!t]) v = v->next[t];
		else v = v->next[!t],ans += (1<<base);
	}
	return ans;
}

int N;

int main(){
	scanf("%d",&N);
	FOR(i,1,N-1){
		int u,v,w;scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	dfs(&node[1]);
	root = New();
	FOR(i,1,N) insert(node[i].dist);
	int ans = 0;
	FOR(i,1,N) ans = std::max(ans,query(node[i].dist));
	printf("%d\n",ans);
	return 0;
} 


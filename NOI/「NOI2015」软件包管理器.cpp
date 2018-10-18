#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
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
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100000 + 5;

struct Node{
	struct Edge *firstEdge;
	struct Chain *chain;
	int dfn,depth,size;
	bool vis;
	Node *fa,*maxChild; 
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;
}pool1[(MAXN<<1) + 1],*frog1 = pool1;

Edge *New(Node *s,Node *t){
	Edge *ret = ++frog1;
	ret->s = s;ret->t = t;
	ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v){
	//DEBUG(u);DEBUG(v);
	node[u].firstEdge = New(&node[u],&node[v]);
	node[v].firstEdge = New(&node[v],&node[u]); 
}

struct Chain{
	Node *top;
}pool2[MAXN+1],*frog2 = pool2;

Chain *New(Node *top){
	Chain *ret = ++frog2;
	ret->top = top;
	return ret;
}

void dfs1(Node *v){
	v->vis = true;
	v->size = 1;
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(!e->t->vis){
			e->t->fa = v;
			e->t->depth = v->depth + 1;
			dfs1(e->t);
			v->size += e->t->size;
			if(!v->maxChild || v->maxChild->size < e->t->size)
				v->maxChild = e->t; 
		}
	}
}

void dfs2(Node *v){
	static int ts = 0;
	v->dfn = ++ts;
	if(!v->fa || v->fa->maxChild != v) v->chain = New(v);
	else v->chain = v->fa->chain;
	if(v->maxChild) dfs2(v->maxChild);
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t->fa == v && e->t != v->maxChild)
			dfs2(e->t);
	}
}

struct SegmentTree *New(int ,int ,SegmentTree *,SegmentTree *);

struct SegmentTree{
	int l,r,sum,tag;
	SegmentTree *lc,*rc;
	
	static SegmentTree *build(int l,int r){
		int mid = (l + r) >> 1;
		return (l == r) ? New(l,r,NULL,NULL) : New(l,r,build(l,mid),build(mid + 1,r));
	}
	
	inline void cover(int delta){
		sum = (r - l + 1) * delta;
		tag = delta;
	}
	
	inline void pushup(){
		sum = lc->sum + rc->sum;
	}
	
	inline void pushdown(){
		if(tag != -1){
			lc->cover(tag);
			rc->cover(tag);
			tag = -1;
		}
	}
	
	inline void modify(int L,int R,int delta){
		if(l == L && r == R){
			cover(delta);
			return;
		}
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) lc->modify(L,R,delta);
		else if(L > mid) rc->modify(L,R,delta);
		else lc->modify(L,mid,delta),rc->modify(mid+1,R,delta);
		pushup();
	}
	
	inline int query(int L,int R){
		if(l == L && r == R) return sum;
		pushdown();
		int mid = (l + r) >> 1;
		if(R <= mid) return lc->query(L,R);
		if(L > mid) return rc->query(L,R);
		return lc->query(L,mid) + rc->query(mid+1,R);
	}
}pool3[MAXN<<2],*frog3 = pool3,*segt;

SegmentTree *New(int l,int r,SegmentTree *lc,SegmentTree *rc){
	SegmentTree *ret = ++frog3;
	ret->l = l;ret->r = r;
	ret->lc = lc;ret->rc = rc;
	ret->sum = 0;ret->tag = -1;
	return ret;
}

inline void split(int root){
	node[root].depth = 1;
	dfs1(&node[root]);
	dfs2(&node[root]);
}

void install(int x,int y=1,int delta=1){
	Node *u = &node[x],*v = &node[y];
	while(u->chain != v->chain){
		if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
		segt->modify(u->chain->top->dfn,u->dfn,delta);
		u = u->chain->top->fa;
	}
	if(u->depth > v->depth) std::swap(u,v);
	segt->modify(u->dfn,v->dfn,delta);
}

void uninstall(int x,int delta=0){
	Node *v = &node[x];
	segt->modify(v->dfn,v->dfn + v->size - 1,delta);
}

int query(int x,int y){
	int ret = 0;
	Node *u = &node[x],*v = &node[y];
	while(u->chain != v->chain){
		if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
		ret += segt->query(u->chain->top->dfn,u->dfn);
		u = u->chain->top->fa; 
	}
	if(u->depth > v->depth) std::swap(u,v);
	return ret + segt->query(u->dfn,v->dfn);
}

int N,M;
char opt[sizeof("uninstall")];

int main(){
	scanf("%d",&N);
	FOR(i,2,N){
		int x;scanf("%d",&x);
		add(++x,i);
	}
	split(1);
	segt = SegmentTree::build(1,N);
	scanf("%d",&M);
	while(M--){
		int v;
		scanf("%s%d",opt,&v);
		v++;
		int t = segt->query(1,N);
		if(opt[0] == 'i')
			install(v);
		else uninstall(v);
		t -= segt->query(1,N);
		printf("%d\n",std::abs(t));
	}
	return 0;
}


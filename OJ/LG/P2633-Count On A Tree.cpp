//有问题！！！不要抄！！！

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

const int MAXN = 100000 + 5;
using std::map;
using std::make_pair;

int N,M,tN;

map<int,int> S;
int a[MAXN],origin[MAXN];

inline void Read(int &x){
	x = 0;char ch = getchar();
	int flag = 1;
	for(;!isdigit(ch);ch = getchar())
		if(ch == '-') flag = -1;
	for(;isdigit(ch);ch = getchar())
		x = (x << 1) + (x << 3) + (ch ^ '0');
	x *= flag;
}

struct Tree{
	int cnt;
	Tree *lc,*rc;
}pool1[MAXN << 5],*frog = pool1,*root[MAXN];

struct Node{
	int size,dfn,depth,num;
	struct Edge *firstEdge;
	struct Chain *chain;
	Node *fa,*maxChild;
	bool vis;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;
}pool2[MAXN * 2],*frog2 = pool2;

struct Chain{
	Node *top;
}pool3[MAXN],*frog3 = pool3;

Tree *New1(){
	Tree *ret = ++frog;
	ret->cnt = 0;
	ret->lc = ret->rc = NULL;
	return ret;
}

Edge *New2(Node *s,Node *t){
	Edge *ret = ++frog2;
	ret->s = s;ret->t = t;
	ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v){
	node[u].firstEdge = New2(&node[u],&node[v]);
	node[v].firstEdge = New2(&node[v],&node[u]);
}

Chain *New3(Node *top){
	Chain *ret = ++frog3;
	ret->top = top;
	return ret;
}

Tree *insert(Tree *prev,int l,int r,int pos){
	Tree *v = New1();
	if(prev){
		v->cnt = prev->cnt;
		v->lc = prev->lc;
		v->rc = prev->rc;
	}
	if(l == r){
		v->cnt++;
		return v;
	}
	int mid = (l + r) >> 1;
	if(pos <= mid) v->lc = insert(prev ? prev->lc : NULL,l,mid,pos);
	else v->rc = insert(prev ? prev->rc : NULL,mid + 1,r,pos);
	v->cnt++;
	return v;
}

void dfs1(Node *v){
	v->vis = true;
	v->size = 1;
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(!e->t->vis){
			e->t->depth = v->depth + 1;
			e->t->fa = v;
			dfs1(e->t);
			v->size += e->t->size;
			if(!v->maxChild || v->maxChild->size < e->t->size)
				v->maxChild = e->t;
		}
	}
}

void dfs2(Node *v){
	static int timer = 0;
	v->dfn = ++timer;

	if(!v->fa || v != v->fa->maxChild)
		v->chain = New3(v);
	else v->chain = v->fa->chain;

	if(v->maxChild) dfs2(v->maxChild);
	
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t->fa == v && e->t != v->maxChild)
			dfs2(e->t);
	}
}

inline void split(int root){
	node[root].depth = 1;
	dfs1(&node[root]);
	dfs2(&node[root]);
}

int Lca(int x,int y){
	Node *u = &node[x],*v = &node[y];
	while(u->chain != v->chain){
		if(u->chain->top->depth < v->chain->top->depth) std::swap(u,v);
		u = u->chain->top->fa;
	}

	if(u->depth > v->depth) std::swap(u,v);
	return u->num;
}

int query(Tree *rl,Tree *rr,Tree *lca,Tree *lca_fa,int l,int r,int k){
	if(l == r) return l;
	int ls = rl->lc->cnt + rr->lc->cnt - lca->lc->cnt - lca_fa->lc->cnt;
	int mid = (l + r) >> 1;
	if(ls >= k) return query(rl ? rl->lc : NULL,rr ? rr->lc : NULL,lca ? lca->lc : NULL,lca_fa ? lca_fa->lc : NULL,l,mid,k);
	else return query(rl ? rl->rc : NULL,rr ? rr->rc : NULL,lca ? lca->rc : NULL,lca_fa ? lca_fa->rc : NULL,mid + 1,r,k - ls);
}

int main(){
	Read(N);Read(M);
	for(int i = 1;i <= N;i++){
		node[i].num = i;
		Read(a[i]);
		S.insert(make_pair(a[i],0));
	}
	for(map<int,int>::iterator it = S.begin();it != S.end();it++){
		it->second = ++tN;
		origin[tN] = it->first;
	}
	for(int i = 1;i <= tN;i++)
		a[i] = S[a[i]];
	for(int i = 1;i <= N;i++)
		root[i] = NULL;
	for(int u,v,i = 1;i < N;i++){
		Read(u);Read(v);
		add(u,v);
	}
	split(1);
	int lastans = 0;
	while(M--){
		int x,y,k,lca;
		Read(x);Read(y);Read(k);
		x ^= lastans;
		lca = Lca(x,y);
		lastans = origin[query(root[x],root[y],root[lca],root[node[lca].fa->num],1,N,k)];
		printf("%d\n",lastans);
	}
	getchar();getchar();
	return 0;
}
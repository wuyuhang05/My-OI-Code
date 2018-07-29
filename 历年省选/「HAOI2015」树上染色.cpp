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

#define LL long long
//#define max(a,b) a > b ? a : b

const int MAXN = 2000 + 5;

int N,K;
LL f[MAXN][MAXN];

struct Node{
	struct Edge *firstEdge;
	int size,num;
}node[MAXN];

struct Edge{
	Node *s,*t;
	int w;
	Edge *next;
}pool[MAXN * 2],*frog = pool;

Edge *New(Node *s,Node *t,int w){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;
	ret->w = w;ret->next = s->firstEdge;
	return ret;
}

void dfs(Node *v,Node *fa){
	v->size = 1;
	f[v->num][0] = f[v->num][1] = 0;
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t == fa) continue;
		dfs(e->t,v);
		v->size += e->t->size;
	}
	for(Edge *e = v->firstEdge;e;e = e->next){
		if(e->t == fa) continue;
		for(int i = std::min(K,v->size);i >= 0;i--){ // 当前树选择点
			for(int j = 0;j <= std::min(i,e->t->size);j++){ // 子树选择点
				if(f[v->num][i-j] != -1){ 
					LL val = (LL)j * (K-j) * e->w + (LL)(e->t->size - j) * (N - K + j - e->t->size) * e->w;
					f[v->num][i] = std::max(f[v->num][i],f[v->num][i-j] + f[e->t->num][j] + val);
				}
			}
		}
	}
}

inline void add(int u,int v,int w){
	node[u].firstEdge = New(&node[u],&node[v],w);
	node[v].firstEdge = New(&node[v],&node[u],w);
}

int main(){
	scanf("%d%d",&N,&K);
	memset(f,-1,sizeof(f));
	for(int i = 1;i <= N;i++) 
		node[i].num = i;
	for(int u,v,w,i = 1;i < N;i++){
		scanf("%d%d%d",&u,&v,&w);
		add(u,v,w);
	}
	dfs(&node[1],&node[0]);
	printf("%lld\n",f[1][K]);
	getchar();getchar();
	return 0;
}
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

const int MAXN = 200000+5;

struct Node{
	struct Edge *firstEdge;
	int d[2];bool vis;
	int num;
}node[MAXN];

struct Edge{
	Node *s,*t;
	Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t){
	Edge *ret = ++frog;
	*ret = (Edge){s,t,s->firstEdge};
	return ret;
}

char str[MAXN];

inline void add(int u,int v){
	node[u].firstEdge = New(&node[u],&node[v]);
	++node[u].d[str[v]-'A'];
}

int N,M;

int main(){
	scanf("%d%d",&N,&M);
	scanf("%s",str+1);
	FOR(i,1,N) node[i].num = i;
	FOR(i,1,M){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);add(v,u);
	}
	std::queue<Node *> q;
	FOR(i,1,N) if(!node[i].d[0] || !node[i].d[1]) q.push(&node[i]),node[i].vis = true;
	int cnt = q.size();
	while(!q.empty()){
		Node *v = q.front();q.pop();
		for(Edge *e = v->firstEdge;e;e = e->next){
			if(!--e->t->d[str[v->num]-'A'] && !e->t->vis){
				q.push(e->t);cnt++;
				e->t->vis = true;
			}
		}
	}
	puts(cnt != N ? "Yes" : "No");
	return 0;
}



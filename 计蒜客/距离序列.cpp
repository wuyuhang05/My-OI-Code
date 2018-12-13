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

const int MAXN = 10000+5;

struct Node{
	struct Edge *firstEdge;
	Node *pre,*suf;bool vis;
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

inline void add(int u,int v){
	node[u].firstEdge = New(&node[u],&node[v]);
}

int N,d[MAXN];

bool dfs(Node *v){
	//DEBUG(v->num);
	for(Edge *e = v->firstEdge;e;e = e->next){
		//DEBUG(e->t->num);
		if(e->t->vis) continue;
		e->t->vis = true;
		if(!e->t->pre || dfs(e->t->pre)){
			e->t->pre = v;
			v->suf = e->t;
			return true;
		}
	}
	return false;
}

inline int solve(){
	int cnt = 0;
	ROF(i,N-1,0){
		FOR(j,0,N) node[j].vis = false;
		cnt += dfs(&node[i]);
	}
	return cnt;
}

int main(){
	scanf("%d",&N);
	FOR(i,0,N-1) scanf("%d",d+i);
	FOR(i,0,N-1){
		ROF(j,N-1,0){
			if(std::min(std::abs(i-j),N-std::abs(i-j)) == d[i]){
				add(i,j);
				//printf("%d %d\n",i,j);
			}
		}
	}
	FOR(i,0,N) node[i].num = i;
	if(solve() == N){
		FOR(i,0,N-1) printf("%d%c",node[i].suf->num,(i == N-1) ? '\n' : ' ');
	}
	else{
		puts("No Answer");
	}
	return 0;
}

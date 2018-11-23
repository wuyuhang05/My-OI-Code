#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define Re register
#define LL long long
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 2000+5;

struct Node{
	struct Edfe *firstEdge;
}node[MAXN];

struct Edge{
	Node *s,*t;
	int d1,d2;
	Edge *next;
}pool[MAXN<<1],*frog = pool;

Edge *New(Node *s,Node *t,int d1,int d2){
	Edge *ret = ++frog;
	ret->s = s;ret->t = t;ret->d1 = d1;ret->d2 = d2;
	ret->next = s->firstEdge;
	return ret;
}

inline void add(int u,int v,int d1,int d2){
	node[u].firstEdge = New(&node[u],&node[v],d1,d2);
	node[v].firstEdge = New(&node[v],&node[u],d1,d2);
}

struct node{
	Node *nd;
	LL t,c;
	bool operator < (const node &other) const {
		return t*c > other.t*other.c;
	}
};

inline vool check()

inline void Dij(int s){
	std::priority_queue<node> q;
	q.push((node){&node[s],0,0});
	while(!q.empty()){
		node v = q.top();q.pop();
	}
}

int main(){
	
	return 0;
}
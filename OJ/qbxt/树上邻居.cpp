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

struct Edge{
	int u,v,w;
	bool operator < (const Edge &other) const {
		return w > other.w;
	}
}e[MAXN];

struct Query{
	int v,k,priority;
	bool operator < (const Query &other) const {
		return k > other.k;
	}
}q[MAXN];

int fa[MAXN],size[MAXN],ans[MAXN];

int find(int x){
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}

void Union(int x,int y){
	int fx = find(x),fy = find(y);
	if(fx == fy) return;
	fa[fy] = fx;
	size[fx] += size[fy];
}

int main(){
	int N,Q;
	scanf("%d%d",&N,&Q);
	for(int i = 1;i <= N;i++){
		fa[i] = i;
		size[i] = 1;
	}
	for(int i = 1;i < N;i++)
		scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
	std::sort(e + 1,e + N);
	for(int i = 1;i <= Q;i++){
		scanf("%d%d",&q[i].k,&q[i].v);
		q[i].priority = i;
	}
	std::sort(q + 1,q + Q + 1);
	int j = 1;
	for(int i = 1;i <= Q;i++){
		while(e[j].w >= q[i].k && j < N){
			Union(e[j].u,e[j].v);
			j++;
		}
		ans[q[i].priority] = size[find(q[i].v)]-1;
	}
	for(int i = 1;i <= Q;i++) printf("%d%c",ans[i],'\n');
	getchar();getchar();
	return 0;
}
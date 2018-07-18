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

const int MAXN = 20000 + 5;
const int MAXM = 100000 + 5;

struct Relationship{
	int u,v,w;

	bool operator < (const Relationship &other) const {
		return w > other.w;
	}
}r[MAXM];

int N,M;
int a[MAXN],b[MAXN];

int find(int x){
	return x == a[x] ? x : a[x] = find(a[x]);
}

void Union(int x,int y){
	int fx = find(x),fy = find(y);
	a[fy] = fx;
}

bool check(int x,int y){
	return find(x) == find(y);
}

int main(){
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= M;i++)
		scanf("%d%d%d",&r[i].u,&r[i].v,&r[i].w);
	for(int i = 1;i <= N;i++) a[i] = i;
	std::sort(r + 1,r + M + 1);
	for(int i = 1;i <= M;i++){
		if(check(r[i].u,r[i].v)){
			printf("%d\n",r[i].w);return 0;
		}
		else{
			if(!b[r[i].u]) b[r[i].u] = r[i].v;
			else Union(b[r[i].u],r[i].v);
			if(!b[r[i].v]) b[r[i].v] = r[i].u;
			else Union(b[r[i].v],r[i].u);
		}
	}
	printf("%d\n",0);
	//getchar();getchar();
	return 0;
}
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

int N,M;
double ans = 0;
const int MAXN = 10000 + 5;

double dist[MAXN];

bool cmp(double a,double b){
	return a > b;
}

int main(){
	scanf("%d%d",&N,&M);
	for(int i = 1;i <= N;i++)
		scanf("%lf",&dist[i]);
	for(int i = 1;i <= M;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		double delta = (double)(w/(double)2);
		dist[u] += delta;dist[v] += delta;
	}
	std::sort(dist + 1,dist + N + 1,cmp);
	for(int i = 1;i <= N;i++){
		if(i & 1) ans += dist[i];
		else ans -= dist[i];
	}
	printf("%.lf",ans);
	getchar();getchar();
	return 0;
}
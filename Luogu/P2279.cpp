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

const int MAXN = 2000+5;

int N;
int fa[MAXN],depth[MAXN],b[MAXN],o[MAXN];

bool cmp(int x,int y){
	return depth[x] > depth[y];
}
int ans = 0;
int main(){
	scanf("%d",&N);b[1] = 1;
	o[1] = o[0] = N;
	FOR(i,2,N){
		scanf("%d",fa+i);
		depth[i] = depth[fa[i]]+1;
		b[i] = i;o[i] = N;
	}
	std::sort(b+1,b+N+1,cmp);
	FOR(i,1,N){
		int v = b[i];
		o[v] = std::min(o[v],std::min(o[fa[v]]+1,o[fa[fa[v]]]+2));
		if(o[v] > 2){
			o[fa[fa[v]]] = 0;ans++;
			o[fa[fa[fa[v]]]] = std::min(o[fa[fa[fa[v]]]],1);
			o[fa[fa[fa[fa[v]]]]] = std::min(o[fa[fa[fa[fa[v]]]]],2);
		}
	}
	printf("%d\n",ans);
	return 0;
}

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

const int MAXN = 200+5;
int N,n,m;

bool G[MAXN][MAXN];
bool vis[MAXN];
int pre[MAXN];
int ans[MAXN],tot;

bool dfs(int v){
	FOR(i,1,N){
		if(G[v][i] && !vis[i]){
			vis[i] = true;
			if(pre[i] == -1 || dfs(pre[i])){
				pre[i] = v;
				return true;
			}
		}
	}
	return false;
}

void solve(){
	int cnt = 0;CLR(pre,-1);
	FOR(i,1,N){
		CLR(vis,0);
		cnt += dfs(i);
	}
	printf("%d\n",cnt);
	FOR(i,1,N){
		if(pre[i] != -1){
			printf("%d %d\n",i,pre[i]);
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);N = n+m;
	int u=0,v=0;
	// DEBUG(N);
	scanf("%d%d",&u,&v);
	while(u != -1 || v != -1){
		G[u][v] = true;
		scanf("%d%d",&u,&v);
	}
	solve();
	return 0;
}

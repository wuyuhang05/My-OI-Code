#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <set>

const int MAXN = 2000 + 5;

int T,k,n,m;

int yh[MAXN + 5][MAXN + 5],ans[MAXN + 5][MAXN + 5];

int main(){
	scanf("%d%d",&T,&k);
	for(int i = 1;i < MAXN;i++)
		yh[i][i] = yh[i][0] = 1;
	for(int i = 2;i < MAXN;i++)
		for(int j = 1;j < i;j++){
			yh[i][j] = (yh[i-1][j] + yh[i-1][j-1])%k;
			if(!yh[i][j]) ans[i][j] = 1;
		}
	for(int i = 2;i < MAXN;i++)
		for(int j = 1;j < MAXN;j++){
			ans[i][j] += ans[i-1][j] + ans[i][j-1] - ans[i-1][j-1];
		}
	while(T--){
		int x,y;
		scanf("%d%d",&x,&y);
		y = (y > x) ? x : y;
		printf("%d\n",ans[x][y]);
	}
	return 0;
}
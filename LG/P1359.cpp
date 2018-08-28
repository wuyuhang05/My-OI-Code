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

const int MAXN = 200 + 5;

int f[MAXN][MAXN];

int main(){
	int N;
	scanf("%d",&N);
	memset(f,0x3f,sizeof(f));
	for(int i = 1;i <= N;i++) f[i][i] = 0;
	for(int i = 1;i < N;i++)
		for(int j = i + 1;j <= N;j++)
			scanf("%d",&f[i][j]);
	for(int k = 1;k <= N;k++)
		for(int i = 1;i <= N;i++)
			for(int j = 1;j <= N;j++)
				f[i][j] = std::min(f[i][j],f[i][k] + f[k][j]);
	printf("%d\n",f[1][N]);
	getchar();getchar();
	return 0;
}
#include <iostream>
#include <cstring>
#include <cstdio>

const int MAXN = 2000 + 5;

int T,K;
int C[MAXN][MAXN],Ans[MAXN][MAXN];

int main(){
	scanf("%d%d",&T,&K);
	memset(C,0,sizeof(C));
	for(int i = 1;i < MAXN;i++){
		C[i][i] = 1;
		C[i][0] = 1;
	}
	for(int i = 2;i < MAXN;i++){
		for(int j = 1;j < i;j++){
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % K;
			if(!a[i][j]){
				Ans[i][j] = 1;
		}
	}
	for(int i = 2;i < MAXN;i++){
		for(int j = 1;j < MAXN;j++){
			Ans[i][j] += Ans[i-1][j] + Ans[i][j-1] - Ans[i-1][j-1];
		}
	}
	while(T--){
		int N,M;
		scanf("%d%d",&N,&M);
		M = (M > N) ? N : M;
		printf("%d\n",Ans[N][M]);
	}
	return 0;
}
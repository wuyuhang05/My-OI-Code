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

#define LL long long

const int MAXN = 3000 + 5;
const int ha = 1000000007;

int yh[MAXN][MAXN];
LL f[MAXN][MAXN];

class Seatfriends{
public:
	int N,K,G;
	void init(){
		memset(yh,0,sizeof(yh));
		yh[0][0] = yh[1][0] = yh[0][1] = 1;
		for(int i = 1;i <= MAXN;i++){
			yh[i][0] = 1;
			for(int j = 1;j <= i;j++)
				yh[i][j] = (yh[i-1][j] + yh[i-1][j-1])%ha;
		}
	}
	int C(int up,int down){
		if(up == 0){
			return down != 1 ? 0 : 1;
		}
		return yh[up][down];
	}

	LL dfs(int i,int j){ //第 i 个人 j 个联通块
		if(f[i][j] != -1)
			return f[i][j];
		if(N - i < j && j >= 2) return 0;
		if(i == K) return f[i][j] = C(N-i,j);
		f[i][j] = 0;
		if(j < G)
			f[i][j] = (f[i][j] + dfs(i + 1,j + 1) * j % ha) % ha;
		if(j == 1 && i == N - 1 && K == N)
			f[i][j] = (f[i][j] + dfs(i + 1,j)) % ha;
		else
			f[i][j] = (f[i][j] + dfs(i + 1,j) * 2 % ha * j % ha)%ha;
		if(j >= 2)
			f[i][j] = (f[i][j] + dfs(i+1,j-1) * j % ha) % ha;
		return f[i][j]%ha;
	}

	int countseatnumb(int N, int K, int G){
		this->N = N;
		this->K = K;
		this->G = G;
		init();
		memset(f,-1,sizeof(f));
		return (dfs(1,1)*N%ha);
	}
};

int main(){
	while(true){
	int N,K,G;
	scanf("%d%d%d",&N,&K,&G);
	printf("%d\n",a.countseatnumb(N,K,G));
	}
	getchar();getchar();
	return 0;
}
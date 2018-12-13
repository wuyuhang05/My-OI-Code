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

const int MAXN = 100+5;
int N,M;
int f[MAXN][MAXN][2];
int pos[MAXN],P[MAXN];
int sum[MAXN];

int main(){
	scanf("%d%d",&N,&M);
	FOR(i,1,N) scanf("%d%d",pos+i,P+i);
	FOR(i,1,N) sum[i] = sum[i-1]+P[i];
	CLR(f,0x3f);
	f[M][M][0] = f[M][M][1] = 0;
	FOR(len,2,N){
		FOR(i,1,N-len+1){
			int j = i+len-1;
			f[i][j][0] = std::min(f[i+1][j][0]+(pos[i+1]-pos[i])*(sum[N]-sum[j]+sum[i]),f[i+1][j][1]+(pos[j]-pos[i])*(sum[i]+sum[N]-sum[j]));
			f[i][j][1] = std::min(f[i][j-1][0]+(pos[j]-pos[i])*(sum[i-1]+sum[N]-sum[j-1]),f[i][j-1][1]+(pos[j]-pos[j-1])*(sum[i-1]+sum[N]-sum[j-1]));
		}
	}
	printf("%d\n",std::min(f[1][N][0],f[1][N][1]));
	return 0;
}


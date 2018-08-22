#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long
#define ULL unsigned long long
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 20 + 5;
const int MAXS = 100000 + 5;
const int ha = 1000000007;

LL N;
LL map[MAXN][MAXN],f[MAXS],g[MAXS];

void pre(LL S){
	g[S] = 1;
	for(LL i = 1;i <= N;i++){
		if((1 << (i-1))&S)
			for(LL j = i + 1;j <= N;j++)
				if((1 << (j-1))&S)
					g[S] = (g[S] * (map[i][j] + 1)) % ha;
	}
}

int main(int argc,char *argv[]){
	scanf("%lld",&N);
	for(int i = 1;i <= N;i++)
		for(int j = 1;j <= N;j++)
			scanf("%lld",&map[i][j]);
	for(LL i = 0;i < (1 << N);i++) pre(i);
	for(LL S = 0;S < (1 << N);S++){
		f[S] = g[S];
		LL i = S ^ (S&-S);
		for(LL j = i;j;j=(j-1)&i) 
			f[S] = (f[S]-g[j]*f[S^j]%ha + ha)%ha;
	}
	printf("%lld\n",f[(1<<N)-1]%ha);
	getchar();getchar();
	return 0;
}

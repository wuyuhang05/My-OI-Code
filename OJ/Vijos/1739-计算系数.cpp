#include <iostream>
#include <cstdio>
#include <cstring>

#define DD getchar();getchar()
#define LL long long
const int ha = 10000 + 7;
const int MAXN = 1000 + 5;

LL A,B,K,N,M;

LL qpow(LL a,LL n){
	LL ret = 1;
	a %= ha;
	while(n){
		if(n & 1) ret = (ret * a) % ha;
		a = (a * a) % ha;
		n >>= 1;
	}
	return ret;
}

LL C[MAXN][MAXN];

int main(){
	scanf("%lld%lld%lld%lld%lld",&A,&B,&K,&N,&M);
	for(int i = 0;i < MAXN;i++){
		C[i][i] = 1;
		C[i][0] = 1;
	}
	for(int i = 1;i <= K;i++){
		for(int j = 1;j <= N;j++){
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % ha;
		}
	}
	LL ans = (qpow(A,N) * qpow(B,M) * C[K][N])%ha;
	printf("%lld\n",ans);
	//getchar();getchar();
	return 0;
}

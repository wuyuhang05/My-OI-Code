#include <iostream>
#include <cstring>
#include <cstdio>

int N,M,K,X;
#define LL long long

LL qpow(int x,int k){
	LL ans = 1;
	x %= N;
	while(k){
		if(k & 1) ans = (ans * x) % N;
		x = (x * x) % N;
		k >>= 1;
	}
	return ans;
}

int main(){
    scanf("%d%d%d%d",&N,&M,&K,&X);
    LL ans = (X + (qpow(10,K)*M)%N)%N;
    printf("%lld\n",ans);
    return 0;
}

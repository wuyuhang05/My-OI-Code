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

LL b,p,k;

LL pow(LL a,LL n){
	LL ret = 1;
	while(n){
		if(n&1) ret = ret * a % k;
		a = a * a % k; 
		n >>= 1;
	}
	return ret % k;
}

int main(){
	scanf("%lld%lld%lld",&b,&p,&k);
	printf("%lld^%lld mod %lld=%lld",b,p,k,pow(b,p));
	getchar();getchar();
	return 0;	
}
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

LL a,b,x,y;

void exgcd(LL a,LL b){
	if(b == 0){
		x = 1;y = 0;
		return;
	}
	exgcd(b,a%b);
	int t = x;x = y;y = t-a/b*y;
	return;
}

int main(){
	scanf("%lld%lld",&a,&b);
	exgcd(a,b);
	printf("%lld\n",(x + b) % b);
	return 0;
}
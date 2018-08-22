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

const int BASE = 12 + 5;

LL f[BASE][BASE];
LL a,b;
int dight[BASE];
int len;

void init(){
	memset(f,0,sizeof(f));
	for(int i = 0;i <= 9;i++){
		f[1][i] = 1;
	}
	for(int i = 2;i <= 10;i++){
		for(int j = 0;j <= 9;j++){
			for(int k = 0;k <= 9;k++){
				if(std::abs(j - k) >= 2)
					f[i][j] += f[i-1][k];
			}
		}
	}
}

LL solve(LL x){
	LL ret = 0;
	if(!x) return 0;
	memset(dight,0,sizeof(dight));
	len = 0;
	while(x){
		dight[++len] = x % 10;
		x /= 10;
	}
	for(int i = 1;i <= dight[len] - 1;i++)
		ret += f[len][i];
	for(int i = len - 1;i > 0;i--)
		for(int j = 1;j <= 9;j++)
			ret += f[i][j];
	for(int i = len-1;i > 0;i--){
		for(int j = 0;j <= dight[i]-1;j++)
			if(std::abs(dight[i + 1]-j) >= 2) ret += f[i][j];
		if(std::abs(dight[i + 1] - dight[i]) < 2) break;
	}
	return ret;
}
	
int main(){
	scanf("%lld%lld",&a,&b);
	init();
	printf("%lld",solve(b + 1) - solve(a));
	getchar();getchar();
	return 0;
}
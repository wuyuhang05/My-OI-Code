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

const int MAXN = 1000 + 5;

int N,K;
int c[MAXN];

bool cmp(int a,int b){
	return a > b;
}

int main(){
	scanf("%d%d",&N,&K);
	for(int i = 1;i <= K;i++)
		scanf("%d",&c[i]);
	std::sort(c + 1,c + K + 1,cmp);
	int l = 1,r = N,ans = 0;
	for(int i = 1;i <= N;i++){
		ans += (r - l) * c[i];
		l++;r--;
		if(l >= r) break;
	}
	printf("%d\n",ans);
	return 0;
}
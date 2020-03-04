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

const int MAXN = 100000000 + 5;

bool vis[MAXN];
int pre[MAXN],ans = 0;

int main(){
	int N;scanf("%d",&N);
	for(int i = 2;i <= N;i++){
		if(!vis[i]) pre[++ans] = i;
		for(int j = 1;j <= ans && pre[j] * i <= N;j++){
			vis[pre[j]*i] = true;
			if(!(i % pre[j])) break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
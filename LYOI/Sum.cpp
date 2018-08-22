#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define LL long long

const int MAXN = 100000;
int a[MAXN];

int main(){
	for(int i = 0;i < MAXN;i++){
		int x = i;
		do
			a[i] += x%10;
		while(x/=10);
	}
	int L,R;
	LL ans = 0;
	scanf("%d%d",&L,&R);
	for(int i = L;i <= R;i++){
		ans += a[i%MAXN] + a[i/MAXN];
	}
	printf("%lld\n",ans);
	return 0;
}
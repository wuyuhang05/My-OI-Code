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

const int MAXN = 100000 + 5;

int N;

struct Cow{
	int t,d;

	bool operator < (const Cow &other) const {
		return ((double)d/(double)t) > ((double)(other.d)/(double)(other.t));
	}
}c[MAXN];

int main(){
	scanf("%d",&N);
	for(int i = 1;i <= N;i++)
		scanf("%d%d",&c[i].t,&c[i].d);
	std::sort(c + 1,c + N + 1);
	LL ans = 0,ts = 0;
	for(int i = 1;i <= N;i++){
		ans += c[i].d * ts;
		ts += c[i].t * 2;
	}
	printf("%lld\n",ans);
	//getchar();getchar();
	return 0;
}
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

using std::pair;
using std::sort;
#define LL long long

const int MAXN = 100000 + 5;

pair<LL,LL> p[MAXN];

int main(int argc, char const *argv[]){
	int N;
	LL ans = 0,ts = 0;
	scanf("%d",&N);
	for(int i = 1;i <= N;i++){
		scanf("%lld%lld",&p[i].second,&p[i].first);
		ans += p[i].second;
	}
	std::sort(p + 1,p + N + 1);
	for(int i = 1;i <= N;i++){
		ts += p[i].first;
		ans -= ts;
	}
	printf("%lld\n",ans);
	getchar();getchar();
	return 0;
}
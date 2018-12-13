#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>
#include <set>
#define Re register
#define LL long long
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int main(){
	int N;scanf("%d",&N);
	int x=0,cnt=0;
	FOR(i,1,N){
		int xx;scanf("%d",&xx);
		if(!cnt){
			cnt++;
			x = xx;
			continue;
		}
		cnt = (x == xx) ? cnt+1 : cnt-1;
	}
	printf("%d\n",x);
	return 0;
}


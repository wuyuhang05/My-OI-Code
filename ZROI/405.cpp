#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <ctime>
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
#define SFOR(i,a,b,c) for(Re int i = a;i <= b;i+=c)
#define SROF(i,a,b,c) for(Re int i = a;i >= b;i-=c)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

int f(int x){
	int a[10],max=0,min=0;
	FOR(i,1,5) a[i] = x % 10,x /= 10;
	std::sort(a + 1,a + 5 + 1);
	FOR(i,1,5) min = min * 10 + a[i];
	ROF(i,5,1) max = max * 10 + a[i];
	return max-min;
}

const int MAXN = 100000 + 5;
int ans[50 + 5][MAXN];

inline void pre(){
	FOR(i,0,MAXN-5){
		ans[0][i] = f(i);
	}
	FOR(i,1,40+5){
		FOR(j,1,MAXN-5){
			//DEBUG(ans[i-1][ans[i-1][j]]);
			ans[i][j] = ans[i-1][ans[i-1][j]];
		}
	}
}

inline void print(int x){
	int base = 10000;
	FOR(i,1,5){
		printf("%d",x/base);
		x %= base;
		base /= 10;
	}
	puts("");
}

int T,c,x;

int main(){
	scanf("%d%d",&T,&c);
	pre();
	while(T--){
		scanf("%d",&x);
		FOR(i,0,31){
			if(c & (1 << i)){
				x = ans[i][x];
			}
		}
		print(x);
	}
	return 0;
}

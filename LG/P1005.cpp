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
#define LL __int128
#define U unsigned
#define FOR(i,a,b) for(Re int i = a;i <= b;++i)
#define ROF(i,a,b) for(Re int i = a;i >= b;--i)
#define CLR(i,a) memset(i,a,sizeof(i))
#define BR printf("--------------------\n")
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;
int a[MAXN];
LL f[MAXN][MAXN],pw[MAXN];
int N,M;
LL ans;

inline void pre(){
	pw[0] = 1;
	FOR(i,1,MAXN-1) pw[i] = pw[i-1]*2ll;
}

inline void print(LL x){
	if(!x) return;
	if(x) print(x/10);
	putchar(x%10+'0');
}

int main(){
	scanf("%d%d",&N,&M);
	pre();
	while(N--){
		FOR(i,1,M) scanf("%d",a+i);
		CLR(f,0);
		FOR(i,1,M){
			ROF(j,M,i){
				f[i][j] = std::max(f[i][j],f[i-1][j] + pw[M-j+i-1]*a[i-1]);
				f[i][j] = std::max(f[i][j],f[i][j+1] + pw[M-j+i-1]*a[j+1]);
			}
		}
		LL max = 0;
		FOR(i,1,M) max = std::max(max,f[i][i] + pw[M]*a[i]);
		ans += max;
	}
	if(ans) print(ans);
	else puts("0");
	return 0;
}

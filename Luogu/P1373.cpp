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

const int MAXN = 800+5;
const int MAXK = 15+5;

const int ha = 1000000000+7;

int f[MAXN][MAXN][MAXK][2];
int N,M,K;
int a[MAXN][MAXN];

inline void add(int &a,int b){
	a += b;if(a >= ha) a -= ha;
}

inline int mod(int a){
	if(a >= K) a -= K;
	if(a < 0) a += K;
	return a;
}

int main(){
	scanf("%d%d%d",&N,&M,&K);K++;
	FOR(i,1,N) FOR(j,1,M) scanf("%d",&a[i][j]);
	FOR(i,1,N) FOR(j,1,M) f[i][j][mod(a[i][j])][0] = 1;
	FOR(i,1,N){
		FOR(j,1,M){
			FOR(k,0,K-1){
				add(f[i][j][k][0],f[i-1][j][mod(k-a[i][j])][1]);
				add(f[i][j][k][0],f[i][j-1][mod(k-a[i][j])][1]);
				add(f[i][j][k][1],f[i-1][j][mod(k+a[i][j])][0]);
				add(f[i][j][k][1],f[i][j-1][mod(k+a[i][j])][0]);
			}
		}
	}
	int ans = 0;
	FOR(i,1,N) FOR(j,1,M) add(ans,f[i][j][0][1]);
	printf("%d\n",ans);
	return 0;
}


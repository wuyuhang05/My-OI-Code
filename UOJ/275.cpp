#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

#define fi first
#define se second
#define U unsigned
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = 1e5 + 5;
const int ha = 1e9 + 7;
const int inv2 = 500000004;
int limn[MAXN],limm[MAXN],tn,tm;
int f[MAXN][2][2],g[MAXN][2][2];
int n,m;

inline void add(int &a,int b){
	(a += b);if(a >= ha) a -= ha;
}

signed main(){
	int T,K;scanf("%lld%lld",&T,&K);
	while(T--){
		scanf("%lld%lld",&n,&m);m = std::min(n,m);
		int ans = (1ll*(m%ha)*((m+1)%ha)%ha*inv2%ha+1ll*((n-m+1)%ha)*((m+1)%ha)%ha)%ha;
		for(;n;n /= K,m /= K) limn[++tn] = n%K,limm[++tm] = m%K;
		CLR(f,0);CLR(g,0);f[tn+1][1][1] = 1;g[tn+1][1][1] = 1;
		ROF(i,tn+1,1){
			FOR(j,0,1){
				FOR(k,0,1){
					if(g[i][j][k]){
						FOR(x,0,(j?limn[i-1]:K-1)){
							FOR(y,0,(k?limm[i-1]:K-1)){
								if(y > x) break;
								add(f[i-1][j&&(x==limn[i-1])][k&&(y==limm[i-1])],f[i][j][k]);
								g[i-1][j&&(x==limn[i-1])][k&&(y==limm[i-1])] = 1;
							}
						}
					}
				}
			}
		}
		FOR(i,0,1) FOR(j,0,1) add(ans,ha-f[1][i][j]);
		printf("%lld\n",ans);
		FOR(i,0,tn) limn[i] = 0;
		FOR(i,0,tm) limm[i] = 0;
		tn = tm = 0;
	}
	return 0;
}
/*
Lucas 定理之后变成:
给定 n,m  问有多少组 x <= n,y <= m 满足
x y 的 k 进制分解下至少有一位 x<y
记 f[i][0/1][0/1][0/1]
表示填了前 i 位 是否有 x<y x 是否卡上界 y 是否卡上界

其实可以考虑补集转化 f[i][0/1][0/1] 表示前 i 位 x,y 是否卡上界 强制 x[i]>=y[i] 即可
*/
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

const int MAXN = 16+1;
const int ha = 19901013;
int f[MAXN][MAXN][(1<<MAXN)+3];
char str[MAXN][MAXN],lim[MAXN][MAXN];
int n,m;
int g[MAXN][MAXN][MAXN][MAXN];
// 上边界 左边界 右边界 下边界

inline void Solve(int u,int l,int r){
	CLR(lim,0);
	FOR(i,u,n) FOR(j,l,r) lim[i-u][j-l] = str[i][j];
	int n = ::n-u+1,m = r-l+1;
	f[0][0][(1<<m)-1] = 1;
	FOR(i,0,n-1){
		FOR(j,0,m-1){
			FOR(S,0,(1<<m)-1){
				int ii,jj;
				if(j != m-1) ii=i,jj=j+1;
				else ii=i+1,jj=0;
				if(lim[i][j] == 'x'){
					(f[ii][jj][S|(1<<j)] += f[i][j][S]) %= ha;
				}
				else{
					int nxt = S;
					if(nxt>>j&1) nxt^=(1<<j);
					(f[ii][jj][nxt] += f[i][j][S]) %= ha;
					if(!(S>>j&1)) (f[ii][jj][S|(1<<j)] += f[i][j][S]) %= ha;
					if(j>0 && !((S>>(j-1))&1)) (f[ii][jj][S|(1<<j)|(1<<(j-1))] += f[i][j][S]) %= ha;
				}
			}
		}
	}
	FOR(i,u,::n){
		FOR(S,0,(1<<m)-1){
			(g[u][l][r][i] += f[i-u+1][0][S]) %= ha;
		}
	}
	FOR(i,0,n+1) FOR(j,0,m+1) FOR(S,0,(1<<m)) f[i][j][S] = 0;
}

int F[MAXN],pc[(1<<MAXN)+3];
std::vector<int> now;

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%s",str[i]+1);
	FOR(i,1,n) FOR(l,1,m) FOR(r,l,m) Solve(i,l,r);
	int ans = 0;
	FOR(S,0,(1<<(n-1))-1){
		CLR(F,0);
		now.clear();
		FOR(i,0,n-2) if((S>>i)&1) now.pb(i+1);
		int las = 0;F[0] = 1;int t = 1;
		FOR(i,1,m){
			t = 1;las = 0;
			for(auto x:now){
				t = 1ll*t*g[las+1][1][i][x]%ha;
				las = x;
			}
			if(n != las) t = 1ll*t*g[las+1][1][i][n]%ha;
			F[i] = t;
			FOR(j,1,i-1){ // [j+1,i]
				t = 1;las = 0;
				for(auto x:now){
					t = 1ll*t*g[las+1][j+1][i][x]%ha;
					las = x;
				}
				if(n != las) t = 1ll*t*g[las+1][j+1][i][n]%ha;
				t = 1ll*t*F[j]%ha;
				(F[i] += ha-t) %= ha;
			}
		}
		if(now.size()&1) F[m] = ha-F[m];
		(ans += F[m]) %= ha;
		// DEBUG(ans);DEBUG(res);
	}
	printf("%d\n",ans);
	return 0;
}
/*
f[i][j][S] 表示放置到了 (i,j) 轮廓线状态为 S 的方案数
如果有障碍: f[i][j][S] -> f[i][j+1][S|(1<<j)]
不放: f[i][j][S] -> f[i][j+1][S'] S'的第 j 位为 0
往上放: f[i][j][S] -> f[i][j+1][S|(1<<j)] if((S>>j&1) == 0)
往左放: f[i][j][S] -> f[i][j+1][S|(1<<j)|(1<<(j-1))] if(j>0 && ((1<<(j-1))==0))
每行到边界换行即可
*/
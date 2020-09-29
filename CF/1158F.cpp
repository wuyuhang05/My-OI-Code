#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 3000+5;
const int ha = 998244353;
int n,c,a[MAXN];

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}

int ans[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

namespace Subtask1{ // O(n^2/c * 2^c)
	int f[2][MAXN][(1<<10)+3],now;
	// 考虑了前i个数 凑了j个[1..c],当前段哪些还没凑
	inline void Solve(){
		int U = (1<<c)-1;
		f[now=0][0][0] = 1;FOR(i,1,n) --a[i];
		FOR(i,1,n){
			FOR(j,0,(i-1)/c) FOR(S,0,U-1) f[now^1][j][S] = f[now][j][S];
			int t = (1<<a[i]);
			FOR(j,0,(i-1)/c){
				FOR(S,0,U-1){
					if(!f[now][j][S]) continue;
					int nS = S|t,nj = j;
					if(nS == U) nS = 0,nj = j+1;
					add(f[now^1][nj][nS],f[now][j][S]);
				}
			}
			now ^= 1;
		}
		FOR(S,0,(1<<c)-2) FOR(j,0,n/c) add(ans[j],f[now][j][S]);
		add(ans[0],ha-1);// 空
	}
}

namespace Subtask2{
	int f[MAXN][MAXN],g[MAXN][MAXN];
	/*
	f[i][j]: 最后一次选的是i,搞出了j个段
	转移需要预处理 g[i][j]: 最后一次选的是j,选出了一段 计算g只需要得到出现次数就行了
	*/
	int cnt[MAXN],now,sm;
	int pw[MAXN],inv[MAXN];
	
	inline void reset(){
		FOR(i,1,c) cnt[i] = 0;now = 0;sm = 1;
	}
	
	inline void add(int x){
		if(!cnt[x]){
			++cnt[x];++now;
			return;
		}
		sm = 1ll*sm*inv[cnt[x]]%ha;
		++cnt[x];
		sm = 1ll*sm*(pw[cnt[x]]+ha-1)%ha;
	}
	
	inline void Solve(){
		pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 2ll*pw[i-1]%ha;
		FOR(i,0,MAXN-1) inv[i] = qpow((pw[i]+ha-1)%ha);
		FOR(r,1,n){
			reset();
			ROF(l,r,1){
				add(a[l]);
				if(now != c) g[l][r] = 0;
				else g[l][r] = 1ll*sm*inv[cnt[a[r]]]%ha;
			}
		}
		f[0][0] = 1;
		FOR(i,0,n-1){
			FOR(j,0,i/c){
				if(!f[i][j]) continue;
				FOR(k,i+c,n){
					::add(f[k][j+1],1ll*f[i][j]*g[i+1][k]%ha);
				}
			}
		}
		// DEBUG(f[2][2]);
		// exit(0);
		FOR(j,0,n/c){
			reset();
			ROF(i,n,0){
				if(!f[i][j]){
					add(a[i]);continue;
				}
				int t=0;
				t = pw[n-i];
				if(now == c) ::add(t,ha-sm);
				::add(ans[j],1ll*f[i][j]*t%ha);
				add(a[i]);
			}
		}
		::add(ans[0],ha-1);
	}
}

int main(){
	scanf("%d%d",&n,&c);
	FOR(i,1,n) scanf("%d",a+i);
	if(c <= 10) Subtask1::Solve();
	else Subtask2::Solve();
	FOR(i,0,n) printf("%d ",ans[i]);puts("");
	return 0;
}
/*
复杂度 O(n^3/log)
*/
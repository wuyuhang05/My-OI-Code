#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,int>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 100+5;
const int MAXM = 1e6 + 5;
const int ha = 1000003;
int n;

namespace Matrix_Tree{
	// 无向图：正常做
	// 有向图：外向树用入度 内向树用出度 删去根所在的行列
	int a[MAXN][MAXN];
	
	inline int qpow(int a,int n=ha-2){
		int res = 1;
		while(n){
			if(n&1) res = 1ll*res*a%ha;
			a = 1ll*a*a%ha;
			n >>= 1;
		}
		return res;
	}
	
	inline int inv(int x){
		return qpow(x);
	}

	inline void add(int u,int v){
	    a[u][u]++;a[u][u] %= ha;
//		a[v][v]++;a[v][v] %= ha;
		(a[u][v] += ha-1)%=ha;
//		(a[v][u] += ha-1)%=ha;
	}

	inline int det(){
		int ans = 1;
		FOR(i,2,n){
			int tmp = i;
			FOR(j,i,n-1) if(a[j][i]) {tmp = j;break;}
			if(tmp != i) std::swap(a[tmp],a[i]),ans = -ans;
			FOR(j,i+1,n){
				if(!a[j][i]) continue;
				int div = 1ll*inv(a[i][i])*a[j][i]%ha;
				FOR(k,i,n) (a[j][k] += ha-1ll*a[i][k]*div%ha) %= ha;
			}
		}
		ans = (ans+ha)%ha;
		FOR(i,2,n) ans = 1ll*ans*a[i][i]%ha;
		return ans;
	}
};
using namespace Matrix_Tree;

int in[MAXN],out[MAXN];
int fac[MAXM];

inline void Solve(){
	FOR(i,1,n) FOR(j,1,n) a[i][j] = 0;
	FOR(i,1,n) in[i] = out[i] = 0;
	FOR(i,1,n){
		int t;scanf("%d",&t);
		while(t--){
			int to;scanf("%d",&to);
			in[to]++;out[i]++;
			add(i,to);
		}
	}
	if(n == 1 && out[1] == 0){
		puts("1");return;
	}
	FOR(i,1,n) if(in[i] != out[i]) {puts("0");return;}
	int ans = det();
	if(ans == 0){
		puts("0");return;
	}
	FOR(i,2,n) ans = 1ll*ans*fac[out[i]-1]%ha;
	ans = 1ll*ans*fac[out[1]]%ha;
	printf("%d\n",ans);
}

int main(){
	fac[0] = 1;
	FOR(i,1,MAXM-1) fac[i] = 1ll*fac[i-1]*i%ha;
	while(~scanf("%d",&n) && n) Solve();
	return 0;
}
/*
1
0
2
1 1
1 2
0
*/
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
const int MAXN = 50+5;
const int MAXM = 1600+5;
const int MAXV = 2e5 + 5;
const int ha = 1000000007;
class AppleTrees{
	int n;
	int f[MAXN][MAXN][MAXM];//考虑前 i 个树 有 j 个空位 压缩距离是 k
	int fac[MAXV],inv[MAXV];
	inline int qpow(int a,int n=ha-2){
		int res = 1;
		while(n){
			if(n & 1) res = 1ll*res*a%ha;
			a = 1ll*a*a%ha;
			n >>= 1;
		}
		return res;
	}

	inline void add(int &x,int y){
		(x += y);if(x >= ha) x -= ha;
	}

	inline int C(int n,int m){
		if(n < m) return 0;
		if(!m) return 1;
		return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
	}
public:
	int theCount(int D,std::vector<int> r){
		n = r.size();std::sort(all(r));
		f[0][0][0] = 1;
		FOR(i,0,n-1){
			FOR(j,0,n){
				FOR(k,0,std::min(1600,D)){
					if(!f[i][j][k]) continue;
					add(f[i+1][j+1][k],f[i][j][k]);
					add(f[i+1][j][k+r[i]],2ll*f[i][j][k]%ha*j%ha);
					if(j > 1)
						add(f[i+1][j-1][k+2*r[i]],1ll*f[i][j][k]*(j-1)%ha*j%ha);
				}
			}
		}
		fac[0] = 1;FOR(i,1,MAXV-1) fac[i] = 1ll*fac[i-1]*i%ha;
		inv[MAXV-1] = qpow(fac[MAXV-1]);ROF(i,MAXV-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
		int ans = 0;
		FOR(i,1,MAXM-1){
			add(ans,1ll*f[n][1][i-1]*C(D-i+n,n)%ha);
		}
		return ans;
	}
};
#ifdef RainAir
AppleTrees tst;
int main(){
	printf("%d\n",tst.theCount(100000
,{21, 37, 23, 13, 32, 22, 9, 39}));
	return 0;
}

#endif
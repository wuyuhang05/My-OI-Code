#include <bits/stdc++.h>

#define fi first
#define se second
#define db double
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
const int ha = 998244353;

inline void add(int &x,int y){
	x += y;if(x >= ha) x -= ha;
}
int f[2][MAXN][MAXN],now;
int fac[MAXN],inv[MAXN];
// 考虑前i个位置,已经使用了j个线段,当前还没结尾的有k个

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void prework(){
	fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
	inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
	return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
	prework();
	int n,m,t;scanf("%d%d%d",&n,&m,&t);
	f[now=0][0][0] = 1;
	FOR(i,1,n){
		CLR(f[now^1],0);
		FOR(j,0,m){// 用了几个线段
			FOR(k,0,std::min(j,t)){ // 现在有几个线段
				if(!f[now][j][k]) continue;
				FOR(a,0,m-j){
					add(f[now^1][j+a][k+a],1ll*f[now][j][k]*C(m-j,a)%ha);
				}
				// FOR(a,0,m-j){// 开头几个
					// FOR(b,0,k){// 结尾几个
						// add(f[now^1][j+a][k-b+a],1ll*f[now][j][k]*C(m-j,a)%ha*C(k,b)%ha);
					// }
				// }可以分两步转移!
			}
		}
		now ^= 1;
		CLR(f[now^1],0);
		FOR(j,0,m){
			FOR(k,0,std::min(j,t)){
				if(!f[now][j][k]) continue;
				FOR(b,0,k){
					add(f[now^1][j][k-b],1ll*f[now][j][k]*C(k,b)%ha);
				}
			}
		}
		now ^= 1;
	}
	printf("%d\n",f[now][m][0]);
	return 0;
}
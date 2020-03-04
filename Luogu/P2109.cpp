/*
* Author: RainAir
* File Name: P2109.cpp
* Date: 2020-02-27 14:57:39
* Last Modified time: 2020-02-27 16:44:30
*/
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

// namespace BF{
// 	int a[MAXM][MAXM],n,k;

// 	inline void add(int u,int v){
// 		a[u][u]++;a[v][v]++;
// 		a[u][v]--;a[v][u]--;
// 	}

// 	inline int det(){
// 		int ans = 1;
// 		FOR(i,1,n-1){
// 			int tmp = i;
// 			FOR(j,i,n-1) if(a[j][i]) {tmp = j;break;}
// 			if(tmp != i) std::swap(a[tmp],a[i]),ans = -ans;
// 			FOR(j,i+1,n-1){
// 				if(!a[j][i]) continue;
// 				int div = 1ll*inv[a[i][i]]*a[j][i]%ha;
// 				FOR(k,i,n) (a[j][k] += ha-1ll*a[i][k]*div%ha) %= ha;
// 			}
// 		}
// 		ans = (ans+ha)%ha;
// 		FOR(i,1,n-1) ans = 1ll*ans*a[i][i]%ha;
// 		return ans;
// 	}

// 	inline int Solve(int n,int k){
// 		CLR(a,0);BF::n = n;BF::k = k;
// 		FOR(i,1,n){
// 			FOR(j,1,k){
// 				if(i-j <= 0) break;
// 				add(i,i-j);
// 			}
// 		}
// 		// FOR(i,1,n) FOR(j,1,n) printf("%d%c",a[i][j]," \n"[j==n]);
// 		FOR(i,1,n) FOR(j,1,n) a[i][j] = (a[i][j]+ha)%ha;
// 		return det();
// 	}
// }

// namespace BM{
// 	int A[MAXN],F[MAXN],G[MAXN];

// 	inline int calc(int p,int f[]){
// 		int res = 0;
// 		FOR(i,1,f[0]) (res += 1ll*A[p-i]*f[i]%ha) %= ha;
// 		return res;
// 	}

// 	inline void work(){
// 		F[F[0] = 1] = 0;G[G[0] = 1] = inv[A[1]];
// 		FOR(i,2,A[0]){
// 			int delta = (A[i]-calc(i,F)+ha)%ha;
// 			if(!delta){
// 				memmove(G+2,G+1,sizeof(int)*G[0]);
// 				G[1] = 0;++G[0];continue;
// 			}
// 			std::swap(F,G);
// 			FOR(i,1,F[0]) F[i] = (1ll*F[i]*delta%ha+G[i]) % ha;
// 			memmove(G+2,G+1,sizeof(int)*G[0]);
// 			G[1] = ha-1;G[0]++;
// 			int tmp = inv[calc(i+1,G)];
// 			FOR(j,1,G[0]) G[j] = 1ll*G[j]*tmp%ha;
// 		}
// 		FOR(i,0,F[0]) printf("%d,",F[i]);puts("");
// 	}

// 	inline void test(){
// 		A[0] = 100;
// 		FOR(i,1,A[0]) A[i] = BF::Solve(i,5);
// 		work();
// 	}
// }

const int MAXN = 50+3;
const int ha = 65521;
// int inv[ha+233];

int S1[60]={0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int S2[60]={0,1,1,3,8,21,55,144,377,987,2584,6765,17711,46368,55872,55727,45788,16116,2560,57085,37653,55874,64448,6428,20357,54643,12530,48468,1832,22549,294,43854,226,22345,1288,47040,8790,44851,60242,4833,19778,54501,12683,49069,3482,26898,11691,8175,12834,30327,12626};
int S3[60]={0,1,1,3,16,75,336,1488,6580,29085,63023,43933,20918,23015,29132,48248,31190,4445,16275,15023,62965,65462,41033,7792,9008,11460,44991,23109,43225,36916,41779,26226,54567,47097,44004,22037,3897,35510,59047,3173,13327,60604,12833,31037,38473,44623,683,39176,35330,7571,25080};
int S4[60]={0,1,1,3,16,125,864,5635,35840,29517,48795,64376,52310,4486,28336,8758,64387,31184,24386,924,17339,37190,56290,63519,16901,29810,10951,54377,10900,7194,45196,49203,6552,6577,27252,8776,26557,8650,16129,47857,498,22234,5918,9943,33404,14096,45895,13602,21648,17129,36233};
int S5[60]={0,1,1,3,16,125,1296,12005,38927,26915,65410,9167,63054,58705,18773,9079,38064,46824,48121,50048,47533,30210,24390,51276,45393,357,44927,15398,15923,31582,56586,25233,41258,21255,21563,16387,39423,26418,10008,6962,42377,50881,54893,50452,23715,53140,52131,57691,13625,19479,37874};

int F1[60] = {1,1}; // (len,...)
int F2[60] = {3,3,65520,0};
int F3[60] = {7,5,65518,3,65516,1,0,0};
int F4[60] = {17,7,65520,65496,31,65469,65437,300,65437,65469,31,65496,65520,7,65520,0,0,0};
int F5[60] = {45,8,5,65489,40,364,63172,62845,2793,7304,50170,14272,13974,32712,27590,63226,30516,31431,62449,44809,2992,62529,20712,3072,34090,35005,2295,37931,32809,51547,51249,15351,58217,62728,2676,2349,65157,65481,32,65516,65513,1,0,0,0,0};
int N;
// #include <cassert>
struct Matrix{
	int a[MAXN][MAXN];
	Matrix(){CLR(a,0);}

	inline Matrix operator * (const Matrix &t) const {
		Matrix res;
		FOR(i,1,N){
			FOR(j,1,N){
				FOR(k,1,N){
					// DEBUG(a[i][k]);DEBUG(t.a[k][j]);
					(res.a[i][j] += 1ll*a[i][k]*t.a[k][j]%ha) %= ha;
					// assert(res.a[i][j] >= 0);
				}
			}
		}
		return res;
	}
}base;

inline Matrix qpow(LL n){
	Matrix res;FOR(i,1,N) res.a[i][i] = 1;
	if(n <= 0) return res;
	while(n){
		if(n & 1) res = res*base;
		base = base*base;
		n >>= 1;
	}
	return res;
}

LL n;
int k;
inline void Solve(int S[],int F[]){
	if(n <= 50){
		printf("%d\n",S[n]);
		return;
	}
	N = F[0];
	FOR(i,1,N) base.a[1][i] = F[i];
	FOR(i,2,N) base.a[i][i-1] = 1;
	Matrix t = qpow(n-F[0]);
	int ans = 0;
	FOR(i,1,N) (ans += 1ll*S[N+1-i]*t.a[1][i]%ha) %= ha;
	printf("%d\n",ans);
}

int main(){
	// inv[1] = 1;
	// FOR(i,2,ha-1) inv[i] = 1ll*(ha-ha/i)*inv[ha%i]%ha;
	scanf("%d%lld",&k,&n);
	if(k == 1) Solve(S1,F1);
	if(k == 2) Solve(S2,F2);
	if(k == 3) Solve(S3,F3);
	if(k == 4) Solve(S4,F4);
	if(k == 5) Solve(S5,F5);
	return 0;
}
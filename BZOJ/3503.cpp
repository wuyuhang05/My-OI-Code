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
const int MAXN = 40+5;
int n,m;
std::bitset<MAXN> S[MAXN];

inline void insert(std::bitset<MAXN> x){
	FOR(i,0,m-1){
		if(!x[i]) continue;
		if(S[i][i]) x ^= S[i];
		else{
			S[i] = x;
			return;
		}
	}
}
std::bitset<MAXN> t;
LL c[MAXN][MAXN];
int a[MAXN][MAXN];
int cnt[MAXN][MAXN];
signed main(){
	scanf("%lld%lld",&n,&m);
	FOR(i,1,m) c[1][i] = 1ll<<(i-1);
	FOR(i,2,n+1){
		FOR(j,1,m){
			// c[i][j] = c[i][j-1]^c[i-1][j+1]^c[i-2][j]^c[i-2][j-1];
			c[i][j] = c[i-1][j-1]^c[i-1][j]^c[i-2][j]^c[i-1][j+1];
		}
	}
	// FOR(i,1,n+1) FOR(j,1,m) printf("%lld%c",c[i][j]," \n"[j==m]);
	FOR(i,0,m-1) FOR(j,0,m-1) S[i][j] = (c[n+1][i+1]>>j)&1ll;
	FOR(i,0,m-1){
		int j = i;
		while(j <= m-1 && !S[j][i]) ++j;
		if(j > m) continue;
		if(i != j) std::swap(S[j],S[i]);
		FOR(k,i+1,m-1) if(S[k][i]) S[k] ^= S[i];
	}
	ROF(i,m-1,0){
		if(!S[i][i]){
			S[i][m] = 1;continue;
		}
		FOR(j,i+1,m-1) S[i][m] = S[i][m]^(S[j][m]*S[i][j]);
	}
	FOR(i,1,m) a[1][i] = S[i-1][m];
	FOR(i,2,n){
		FOR(j,1,m){
			FOR(k,1,m){
				if((c[i][j]>>(k-1))&1) a[i][j] ^= a[1][k];
			}
			// a[i][j] = a[i-1][j-1]^a[i-1][j]^a[i-2][j]^a[i-1][j+1];
		}
	}
	FOR(i,1,n) FOR(j,1,m) printf("%lld%c",a[i][j]," \n"[j==m]);
	// FOR(i,1,n) FOR(j,1,m) if(a[i][j]) ++cnt[i][j],++cnt[i-1][j],++cnt[i+1][j],++cnt[i][j-1],++cnt[i][j+1];
	// FOR(i,1,n) FOR(j,1,m) printf("%lld%c",cnt[i][j]," \n"[j==m]);
	// FOR(i,1,n) FOR(j,1,m) assert(cnt[i][j]%2==0);
	return 0;
}
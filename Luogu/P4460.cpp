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

const int MAXN = 20;
const int ha = 1e8 + 7;
const double EPS = 1e-8;
int x[MAXN],y[MAXN];
int mp[MAXN][MAXN]; // 两点之间有哪些点
int f[(1<<MAXN)+3][MAXN]; // 结尾是 i 经过了 S 这些点
int n;

inline int sgn(double x){
	return std::fabs(x) <= EPS ? 0 : (x > 0 ? 1 : -1);
}

inline double dis(int i,int j){
	int X = x[i]-x[j],Y = y[i]-y[j];
	return std::sqrt(1.0*X*X+1.0*Y*Y);
}

inline bool chk(int i,int j,int k){
	return !sgn(dis(i,k)+dis(j,k)-dis(i,j));
}

int pc[(1<<MAXN)+3];

int main(){
	scanf("%d",&n);
	FOR(i,1,(1<<MAXN)-1) pc[i] = pc[i>>1]+(i&1);
	FOR(i,0,n-1) scanf("%d%d",x+i,y+i);
	FOR(i,0,n-1){
		FOR(j,i+1,n-1){
			FOR(k,0,n-1){
				if(k != i && k != j && chk(i,j,k)) mp[i][j] |= (1<<k);
			}
			mp[j][i] = mp[i][j];
		}
	}
	FOR(i,0,n-1) f[1<<i][i] = 1;
	FOR(S,1,(1<<n)-1){
		FOR(i,0,n-1){
			if(!((S>>i)&1)) continue;
			FOR(j,0,n-1){
				if((S>>j)&1) continue;
				if((S|mp[i][j]) != S) continue;
				(f[S|(1<<j)][j] += f[S][i]) %= ha;
			}
		}
	}
	int ans = 0;
	FOR(S,1,(1<<n)-1){
		if(pc[S] < 4) continue;
		FOR(i,0,n-1){
			(ans += f[S][i])%=ha;
		}
	}
	printf("%d\n",ans);
	return 0;
}
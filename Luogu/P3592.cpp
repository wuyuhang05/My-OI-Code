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

const int MAXN = 50+5;
const int MAXM = 4000+5;
int n,m,N;
int a[MAXM],b[MAXM],c[MAXM];
std::vector<int> S;
int f[MAXN][MAXN][MAXM],g[MAXN][MAXM];
int h[MAXN][MAXN][MAXM],sf[MAXN][MAXN][MAXM];
// f:区间[l,r]最小值为 k
// g: 经过点 j ,c>=i 的区间个数
// f[l][r][k] = f[l][p-1][k']+f[p+1][r][l']+g[k][p]*p[k']
int ans[MAXN];

inline void dfs(int l,int r,int k){
	if(l > r) return;
	int x = h[l][r][k=sf[l][r][k]];
	ans[x] = S[k-1];
	dfs(l,x-1,k);dfs(x+1,r,k);
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,m){
		scanf("%d%d%d",a+i,b+i,c+i);
		S.pb(c[i]);
	}
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());N = S.size();
	FOR(i,1,m) c[i] = std::lower_bound(all(S),c[i])-S.begin()+1;
	FOR(len,1,n){
		FOR(l,1,n-len+1){
			int r = l+len-1;
			CLR(g,0);
			FOR(i,1,m) if(l <= a[i] && b[i] <= r) FOR(j,a[i],b[i]) g[j][c[i]]++;
			FOR(i,l,r) ROF(j,N,1) g[i][j] += g[i][j+1];
			ROF(k,N,1){
				int mx = 0;
				FOR(p,l,r){
					int t = f[l][p-1][k]+f[p+1][r][k]+S[k-1]*g[p][k];
					if(t >= mx) mx = t,h[l][r][k] = p;
					// f[l][r][k] = std::max(f[l][r][k],f[l][p-1][k]+f[p+1][r][k]+S[k-1]*g[p][k]);
				}
				if(mx >= f[l][r][k+1]) f[l][r][k] = mx,sf[l][r][k] = k;
				else f[l][r][k] = f[l][r][k+1],sf[l][r][k] = sf[l][r][k+1];
				// f[l][r][k] = std::max(f[l][r][k],f[l][r][k+1]);
			}
		}
	}
	printf("%d\n",f[1][n][1]);
	// DEBUG(sf[1][n][1]);
	// DEBUG(h[1][n][sf[1][n][1]]);
	dfs(1,n,1);
	FOR(i,1,n) printf("%d ",ans[i]);puts("");
	return 0;
}
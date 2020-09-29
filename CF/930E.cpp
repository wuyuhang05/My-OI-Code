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

const int MAXN = 5e5 + 5;
const int ha = 1e9 + 7;

std::vector<int> S;
int k,m0,m1,n;
P a[2][MAXN];
int lim[2][MAXN];
int f[2][MAXN];
// int f[2][105][105];

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
	x += y;if(x >= ha) x -= ha;
}

int main(){
	scanf("%d%d%d",&k,&m0,&m1);
	FOR(i,1,m0){
		scanf("%d%d",&a[0][i].fi,&a[0][i].se);
		S.pb(a[0][i].fi-1);S.pb(a[0][i].se);
	}
	FOR(i,1,m1){
		scanf("%d%d",&a[1][i].fi,&a[1][i].se);
		S.pb(a[1][i].fi-1);S.pb(a[1][i].se);
	}
	S.pb(0);S.pb(k);
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	CLR(lim,-1);
	FOR(i,1,m0){
		a[0][i].fi = std::lower_bound(all(S),a[0][i].fi-1)-S.begin();
		a[0][i].se = std::lower_bound(all(S),a[0][i].se)-S.begin();
		lim[0][a[0][i].se] = std::max(lim[0][a[0][i].se],a[0][i].fi);
	}
	FOR(i,1,m1){
		a[1][i].fi = std::lower_bound(all(S),a[1][i].fi-1)-S.begin();
		a[1][i].se = std::lower_bound(all(S),a[1][i].se)-S.begin();
		lim[1][a[1][i].se] = std::max(lim[1][a[1][i].se],a[1][i].fi);
	}
	n = S.size();
	FOR(i,0,1) FOR(j,1,n) lim[i][j] = std::max(lim[i][j],lim[i][j-1]);
	f[0][0] = 1;int sm0=1,tp0=0,sm1=0,tp1=0;
	FOR(i,0,n-2){
		while(tp0 <= lim[1][i]) add(sm0,ha-f[0][tp0]),tp0++;
		while(tp1 <= lim[0][i]) add(sm1,ha-f[1][tp1]),tp1++;
		int gx = (qpow(2,S[i+1]-S[i]-1)+ha-1)%ha;
		gx = 1ll*gx*(sm0+sm1)%ha;
		add(f[0][i+1],gx);add(f[1][i+1],gx);
		add(f[0][i],sm1);add(f[1][i],sm0);
		int t0 = sm0,t1 = sm1;
		add(sm0,gx);add(sm1,gx);
		add(sm0,t1);add(sm1,t0);
	}
	// f[0][0][0] = 1;
	// FOR(i,0,n-2){
		// FOR(j,0,i){
			// if(j > lim[1][i]){
				// add(f[0][i+1][j],f[0][i][j]);
				// add(f[1][i+1][i],f[0][i][j]);
				// int gx = (qpow(2,S[i+1]-S[i]-1)+ha-1)%ha;
				// gx = 1ll*gx*f[0][i][j]%ha;
				// add(f[0][i+1][i+1],gx);
				// add(f[1][i+1][i+1],gx);
			// }
			// else f[0][i][j] = 0;
			// if(j > lim[0][i]){
				// add(f[1][i+1][j],f[1][i][j]);
				// add(f[0][i+1][i],f[1][i][j]);
				// int gx = (qpow(2,S[i+1]-S[i]-1)+ha-1)%ha;
				// gx = 1ll*gx*f[1][i][j]%ha;
				// add(f[1][i+1][i+1],gx);
				// add(f[0][i+1][i+1],gx);
			// }
			// else f[1][i][j] = 0;
		// }
	// }
	// 1 2 3 5
	// DEBUG(f[0][4][4]);DEBUG(f[0][4][3]);
	int ans = 0;
	FOR(i,0,n) if(i > lim[1][n]) add(ans,f[0][i]);
	FOR(i,0,n) if(i > lim[0][n]) add(ans,f[1][i]);
	printf("%d\n",ans);
	// DEBUG(ans);
	return 0;
}

/*
f[0/1][i][j] 表示考虑到第i个点,上一个和这个点颜色不同的地方是j
定义 i 所在的块是 (x[i-1],x[i]]
pre 表示前面最远的哪一个块必须有0/1
f[0][i][j] -> f[0][i+1][j](pre[1][i+1] <= j)
f[0][i][j] -> f[1][i+1][i](pre[0][i+1] <= j)
(2^{x[i+1]-x[i]-1}-1)f[0][i][j] -> f[0][i+1][i+1]\f[1][i+1][i+1](pre[1][i+1] <= j\pre[0][i+1] <= j)
*/
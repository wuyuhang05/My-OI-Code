#pragma GCC optimize("Ofast")
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
#define FOR(i,a,b) for(register int i = a;i <= b;++i)
#define ROF(i,a,b) for(register int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 4e4+5;
const int MAXM = 5;
int R[MAXN][MAXM],D[MAXN][MAXM];
int n,m,k;
LL f[2][(1<<MAXM)+2],inf;
int g[2][(1<<MAXM)+2],now;

inline char nc(){
	#define SIZE 1000000+3
	static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
	if(p1 == p2){
		p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
		if(p1 == p2) return -1;
	}
	return *p1++;
	#undef SIZE
}

template <typename T>
inline void read(T &x){
	x = 0;int flag = 0;char ch = nc();
	while(!isdigit(ch)){
		if(ch == '-') flag = 1;
		ch = nc();
	}
	while(isdigit(ch)){
		x = (x<<1) + (x<<3) + (ch^'0');
		ch = nc();
	}
	if(flag) x = -x;
}

inline int chk(LL ext){
	CLR(f[0],0x3f);CLR(g[0],0);now = 0;
	inf = f[0][0];
	f[0][0] = 0;
	FOR(i,0,n-1){
		FOR(j,0,m-1){
			CLR(f[now^1],0x3f);CLR(g[now^1],0);
			FOR(S,0,(1<<(m+1))-1){
				if(f[now][S] == inf) continue;
				// 竖着的边
				if(i != 0 && !((S>>j)&1) && !((S>>m)&1)){// !优先级很高 放在最外边
					int nxt = S;nxt |= (1<<j);
					if((nxt>>(j+1))&1) nxt ^= (1<<(j+1)),nxt |= (1<<m);
					LL gx = f[now][S]+D[i-1][j]+ext;
					if(f[now^1][nxt] > gx || (f[now^1][nxt] == gx && g[now^1][nxt] < g[now][S]+1)){
						f[now^1][nxt] = gx;g[now^1][nxt] = g[now][S]+1;
					}
				}
				// 横着的边
				if(j != 0 && !((S>>j)&1) && !((S>>(j-1))&1)){
					int nxt = S;nxt |= (1<<j);nxt |= (1<<(j-1));
					if((nxt>>m)&1) nxt ^= (1<<m);
					if((nxt>>(j+1))&1) nxt ^= (1<<(j+1)),nxt |= (1<<m);
					LL gx = f[now][S]+R[i][j-1]+ext;
					if(f[now^1][nxt] > gx || (f[now^1][nxt] == gx && g[now^1][nxt] < g[now][S]+1)){
						f[now^1][nxt] = gx;g[now^1][nxt] = g[now][S]+1;
					}
				}
				// 啥都不用
				int nxt = S;
				if((nxt>>m)&1) nxt ^= (1<<m);
				if((nxt>>(j+1))&1) nxt ^= (1<<(j+1)),nxt |= (1<<m);
				LL gx = f[now][S];
				if(f[now^1][nxt] > gx || (f[now^1][nxt] == gx && g[now^1][nxt] < g[now][S])){
					f[now^1][nxt] = gx;g[now^1][nxt] = g[now][S];
				}
			}
			now ^= 1;
//			if(i == 1 && j == 0) DEBUG(f[now][13]);
		}
		CLR(f[now^1],0x3f);CLR(g[now^1],0);
		FOR(S,0,(1<<(m+1))-1){
			int nxt = S;if((nxt>>m)&1) nxt ^= (1<<m);
			if(nxt&1) nxt--,nxt |= (1<<m);
			LL gx = f[now][S];
			if(f[now^1][nxt] > gx || (f[now^1][nxt] == gx && g[now^1][nxt] < g[now][S])){
				f[now^1][nxt] = gx;g[now^1][nxt] = g[now][S];
			}
		}
		now ^= 1;
	}
	LL mn = inf;int ps = -1;
	FOR(S,0,(1<<(m+1))-1){
		if(mn > f[now][S] || (mn == f[now][S] && ps < g[now][S])){
			mn = f[now][S];ps = g[now][S];
		}
	}
//	DEBUG(mn);
	return ps;
}

inline void Solve(){
	read(n);read(m);read(k);
	FOR(i,0,n-2) FOR(j,0,m-1) read(D[i][j]);
	FOR(i,0,n-1) FOR(j,0,m-2) read(R[i][j]);
	LL l = -1e14,r = 0,ans = 0;
//	DEBUG(chk(-4));
//	exit(0);
	while(l <= r){
		LL mid = (l + r) >> 1;
		if(chk(mid) >= k) ans = mid,l = mid+1;
		else r = mid-1;
	}
	chk(ans);//DEBUG(ans);
	LL mn = inf;int ps = -1;
	FOR(S,0,(1<<(m+1))-1){
		if(mn > f[now][S]){
			mn = f[now][S];ps = g[now][S];
		}
	}
//	DEBUG(ps);DEBUG(mn);
	printf("%lld\n",mn-k*ans);
//	FOR(i,0,n) FOR(j,0,m) D[i][j] = R[i][j] = 0;
}

int main(){
//	freopen("../TestData/a.in","r",stdin);
//	freopen("../TestData/aa.out","w",stdout);
	int T;read(T);
	while(T--) Solve();
	return 0;
}

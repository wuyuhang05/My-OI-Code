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

const int MAXN = 22;
const int ha = 998244353;
const int inv2 = 499122177;
int n,m,p;
int w[MAXN];
int e[MAXN][MAXN],pc[(1<<MAXN)+3];
int f[MAXN][(1<<MAXN)+3],g[MAXN][(1<<MAXN)+3],sm[(1<<MAXN)+3],ism[(1<<MAXN)+3];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void FMT(int f[]){
	for(int mid = 1;mid < (1<<n);mid <<= 1){
		for(int i = 0;i < (1<<n);i += (mid<<1)){
			FOR(j,0,mid-1){
				(f[i+mid+j] += f[i+j])%=ha;
			}
		}
	}
}

inline void iFMT(int f[]){
	for(int mid = (1<<(n-1));mid;mid >>= 1){
		for(int i = 0;i < (1<<n);i += (mid<<1)){
			FOR(j,0,mid-1){
				(f[i+mid+j] += ha-f[i+j]) %= ha;
			}
		}
	}
}

int F[MAXN];

inline int find(int x){
	return x == F[x] ? x : F[x] = find(F[x]);
}
int du[MAXN];
inline bool chk(int S){
	if(pc[S] == 1) return 0;
	FOR(i,0,n-1) F[i] = i,du[i] = 0;
	FOR(i,0,n-1){ 
		if(!((S>>i)&1)) continue;
		FOR(j,i+1,n-1){
			if(!((S>>j)&1)) continue;
			if(!e[i][j]) continue;
			du[i]++;du[j]++;
			int x = find(i),y = find(j);
			if(x != y) F[y] = x;
		}
	}
	int lst = -1;
	FOR(i,0,n-1){
		if(!((S>>i)&1)) continue;
		if(lst == -1) {lst = find(i);continue;}
		if(lst != find(i)) return 1;
	}
	FOR(i,0,n-1) if(du[i]&1) return 1;
	return 0;
}

int main(){
	scanf("%d%d%d",&n,&m,&p);
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);u--;v--;
		e[u][v] = e[v][u] = 1;
	}
	FOR(i,1,(1<<MAXN)) pc[i] = pc[i>>1]+(i&1);
	FOR(i,0,n-1) scanf("%d",w+i);
	FOR(S,1,(1<<n)-1){
		FOR(i,0,n-1) sm[S] += w[i]*((S>>i)&1);
		sm[S] = qpow(sm[S],p);ism[S] = qpow(sm[S]);
		if(chk(S)) g[pc[S]][S] = sm[S];
		// DEBUG(g[pc[S]][S]);
	}
	f[0][0] = 1;FMT(f[0]);
	FOR(i,0,n) FMT(g[i]);
	FOR(i,1,n){
		FOR(j,0,i-1){
			FOR(S,0,(1<<n)-1){
				(f[i][S] += 1ll*f[j][S]*g[i-j][S]%ha)%=ha;
			}
		}
		iFMT(f[i]);
		FOR(S,0,(1<<n)-1){
			if(pc[S] == i) f[i][S] = 1ll*f[i][S]*ism[S]%ha;
			else f[i][S] = 0;
		}
		if(i != n) FMT(f[i]);
	}
	printf("%d\n",f[n][(1<<n)-1]);
	return 0;
}
/*
设f[S]表示选取 S 的答案和
g[S] 表示 S 作为一个连通块的贡献
g[S]f[S] = f[T]g[S-T] O(3^n)

子集卷积
f[i][S] 表示 S 大小为 i
f[i][S]*f[j][T] -> f[i+j][S|T]
O(n^2 2^n)
*/
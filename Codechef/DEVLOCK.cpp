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

const int ha = 998244353;
const int G = 3;
const int Gn = 332748118;

const int MAXN = 1e5 + 5;
const int MAXP = 50+5;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct Poly{
	std::vector<int> x;
	inline int deg(){return x.size()-1;}
	inline void ext(int n){x.resize(n+1);}
	inline int& operator [] (const int &t){return x[t];}
};

int r[MAXN<<1],N,len;

inline void init(int n){
	N = 1;len = 0;while(N <= n) N <<= 1,len++;
	FOR(i,0,N-1) r[i] = r[i>>1]>>1|((i&1)<<(len-1));
}

inline void NTT(Poly &A,int opt){
	A.ext(N);
	FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1;mid < N;mid <<= 1){
		int W = qpow(opt==-1?Gn:G,(ha-1)/(mid<<1));
		for(int i = 0;i < N;i += (mid<<1)){
			for(int j = 0,w = 1;j < mid;j++,w = 1ll*w*W%ha){
				int x = A[i+j],y = 1ll*w*A[i+mid+j]%ha;
				A[i+j] = (x+y)%ha;
				A[i+mid+j] = (x+ha-y)%ha;
			}
		}
	}
	if(opt == -1){
		int inv = qpow(N);
		FOR(i,0,N-1) A[i] = 1ll*A[i]*inv%ha;
	}
}

inline Poly operator + (Poly A,Poly B){
	if(A.deg() < B.deg()) std::swap(A,B);
	FOR(i,0,B.deg()) (A[i] += B[i])%=ha;
	return A;
}

inline Poly operator - (Poly A,Poly B){
	if(A.deg() < B.deg()) std::swap(A,B);
	FOR(i,0,B.deg()) (A[i] += ha-B[i]) %= ha;
	return A;
}

inline Poly operator * (Poly A,Poly B){
	int len = A.deg()+B.deg();init(len);
	NTT(A,1);NTT(B,1);
	FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
	NTT(A,-1);A.ext(len);
	return A;
}

inline Poly qpow(Poly A,int n,int mod){
	Poly res;res.ext(mod);
	if(n == 0){
		res[0] = 1;return res;
	}
	A.ext(mod);n--;res = A;
	while(n){
		if(n & 1) {res = res*A;res.ext(mod);}
		A = A*A;A.ext(mod);
		n >>= 1;
	}
	return res;
}

int n,p,m;
int num[MAXP],num2[MAXP];
Poly f[MAXP];// [%p][+]
Poly g[MAXP][MAXP];// [%p][+]
Poly ans[MAXP],tmp[MAXP];
bool vis[100];
int pm[MAXN];
int main(){
	scanf("%d%d%d",&n,&p,&m);
	int t = 1%p;
	if(n <= p){
		FOR(i,1,n){
			num[t]++;
			t = 10*t%p;
		}
	}
	else{
		FOR(i,1,p){
			num[t]++;
			t = 10*t%p;
		}
		n -= p;int len = 0;int st = t;
		FOR(i,1,p){
			if(vis[t]) break;len++;vis[t] = 1;
			num2[t]++;
			t = 10*t%p;
		}
		t = st;//DEBUG(len);
		FOR(i,0,p-1) num[i] += num2[i]*(n/len);
		FOR(i,1,n%len) num[t]++,t = 10*t%p;
		n += p;
	}
	// FOR(i,0,9) DEBUG(num[i]);
	FOR(i,0,p-1) FOR(j,0,p-1) g[i][j].ext(m);
	FOR(i,0,p-1){
		f[i].ext(9);FOR(j,0,9) f[i][j] = 1;
		f[i] = qpow(f[i],num[i],m);
		FOR(j,0,m) (g[i][i*j%p][j] += f[i][j])%=ha;
		// DEBUG(i);
		// FOR(a,0,p-1) FOR(b,0,m) printf("%d%c",g[i][a][b]," \n"[b==m]);
	}
	init(2*m);//DEBUG(N);
	FOR(i,0,p-1) ans[i] = g[0][i];
	FOR(i,1,p-1) FOR(j,0,p-1) NTT(g[i][j],1);
	FOR(i,1,p-1){
		FOR(j,0,p-1) tmp[j].x.clear(),tmp[j].ext(N);
		FOR(j,0,p-1) NTT(ans[j],1);
		FOR(x,0,p-1){
			FOR(y,0,p-1){
				FOR(j,0,N){
					(tmp[(x+y)%p][j] += 1ll*ans[x][j]*g[i][y][j]%ha)%=ha;
				}
			}
		}
		FOR(j,0,p-1) ans[j] = tmp[j];
		FOR(j,0,p-1) NTT(ans[j],-1),ans[j].ext(m);
	}
	// NTT(ans[0],-1);
	FOR(i,1,m) (ans[0][i] += ans[0][i-1])%=ha;
	FOR(i,0,m) printf("%d ",ans[0][i]);puts("");
	return 0;
}
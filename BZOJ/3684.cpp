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

const int MAXN = 2e5 + 5;
const int ha = 950009857;
const int G = 7;
const int Gi = 135715694;

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
	inline int& operator [] (const int &n){return x[n];}
};

int r[MAXN<<2],N;

inline void init(int n){
	N = 1;int len = 0;while(N <= n) N <<= 1,len++;
	FOR(i,0,N-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
}

inline void NTT(Poly &A,int opt){
	A.ext(N);
	FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1;mid < N;mid <<= 1){
		int W = qpow(opt==-1?Gi:G,(ha-1)/(mid<<1));
		for(int i = 0;i < N;i += (mid<<1)){
			for(int j=0,w=1;j < mid;j++,w = 1ll*w*W%ha){
				int x = A[i+j],y = 1ll*w*A[i+mid+j]%ha;
				A[i+j] = (x+y)%ha;A[i+mid+j] = (x+ha-y)%ha;
			}
		}
	}
	if(opt == -1){
		int inv = qpow(N);
		FOR(i,0,N-1) A[i] = 1ll*A[i]*inv%ha;
	}
}

inline Poly operator * (Poly A,Poly B){
	int len = A.deg()+B.deg();init(len);
	NTT(A,1);NTT(B,1);
	FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
	NTT(A,-1);A.ext(len);return A;
}

inline Poly Inv(Poly A){
	int n = A.deg();Poly B;
	A.ext(n*4);B.ext(0);B[0] = qpow(A[0]);
	int len;
	for(len = 1;len <= 2*n;len <<= 1){
		Poly a,b;a.ext(len-1);b.ext(len-1);
		FOR(i,0,len-1) a[i] = A[i],b[i] = B[i];
		init(len);
		NTT(a,1);NTT(b,1);B.ext(N-1);
		FOR(i,0,N-1) B[i] = 1ll*(2ll-1ll*a[i]*b[i]%ha+ha)%ha*b[i]%ha;
		NTT(B,-1);FOR(i,len,N-1) B[i] = 0;
	}
	B.ext(n);
	return B;
}

inline Poly qpow(Poly A,int n,int mod){
	A.ext(mod);Poly res;res.ext(mod);res[0] = 1;
	while(n){
		if(n & 1) {res = res*A;res.ext(mod);}
		A = A*A;A.ext(mod);
		n >>= 1;
	}
	return res;
}

int n,m;
int a[MAXN];
int main(){
	scanf("%d%d",&n,&m);
	Poly G;G.ext(n);
	FOR(i,1,m){
		int x;scanf("%d",&x);
		G[x-1]--;
	}
	G[0]++;
	FOR(i,0,n) (G[i] += ha)%=ha;
	G = Inv(G);
	G = qpow(G,n,n-1);
	printf("%lld\n",1ll*qpow(n)*G[n-1]%ha);
	return 0;
}
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

const int MAXN = 1e5 + 5;
const int ha = 998244353;
const int G = 3;
const int Gn = 332748118;

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
	(x += y);while(x >= ha) x -= ha;
}

struct Poly{
	std::vector<int> x;
	inline int deg(){return (int)x.size()-1;}
	inline void ext(int n){x.resize(n+1);}
	inline int& operator [] (const int &p){return x[p];}
};

Poly operator + (Poly a,Poly b){
	if(a.deg() < b.deg()) std::swap(a,b);
	FOR(i,0,b.deg()) add(a[i],b[i]);
	return a;
}

Poly operator - (Poly a,Poly b){
	bool flag = 0;
	if(a.deg() < b.deg()) std::swap(a,b),flag = 1;
	FOR(i,0,b.deg()) add(a[i],ha-b[i]);
	if(flag) FOR(i,0,a.deg()) a[i] = (ha-a[i])%ha;
	return a;
}

int N,r[MAXN<<2];
int W[MAXN],Wn[MAXN];

inline void prework(){
	FOR(i,0,20){
		W[i] = qpow(G,(ha-1)/(1<<(i+1)));
		Wn[i] = qpow(Gn,(ha-1)/(1<<(i+1)));
	}
}

inline void init(int n){
	int len = 0;N = 1;while(N <= n) N <<= 1,len++;
	FOR(i,0,N-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
}

inline void NTT(Poly &A,int opt){
	A.ext(N);if(!W[0]) prework();
	FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1,cnt = 0;mid < N;mid <<= 1,cnt++){
		int W = opt==-1?(::Wn[cnt]):(::W[cnt]);
		for(int i = 0;i < N;i += (mid<<1)){
			for(int w=1,j = 0;j < mid;j++,w = 1ll*w*W%ha){
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

Poly operator * (Poly A,Poly B){
	int len = A.deg()+B.deg();init(len);
	NTT(A,1);NTT(B,1);
	FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
	NTT(A,-1);A.ext(len);
	return A;
}

Poly Inv(Poly A){
	int n = A.deg();
	Poly B;A.ext(n*4);B.ext(0);
	B[0] = qpow(A[0]);
	int len;
	for(len = 1;len <= n*2;len <<= 1){
		Poly a,b;a.ext(len-1);b.ext(len-1);
		FOR(i,0,len-1) a[i] = A[i],b[i] = B[i];
		init(len);//assert(N==len*2);
		NTT(a,1);NTT(b,1);B.ext(N-1);
		FOR(i,0,N-1) B[i] = 1ll*(2ll-1ll*a[i]*b[i]%ha+ha)%ha*b[i]%ha;
		NTT(B,-1);FOR(i,len,N-1) B[i] = 0;
	}
	B.ext(n);
	return B;
}

Poly operator % (Poly A,Poly B){
	int n = A.deg(),m = B.deg();
	if(n < m) return A;
	Poly a = A,b = B;std::reverse(all(a.x));std::reverse(all(b.x));
	a.ext(n-m);b.ext(n-m);
	b = Inv(b);a = a*b;a.ext(n-m);std::reverse(all(a.x));
	Poly R = A-B*a;R.ext(m-1);
	return R;
}

int n,k;
int f[MAXN],a[MAXN];
// std::mt19937 g(time(NULL));
int main(){
	scanf("%d%d",&n,&k);
	FOR(i,1,k) scanf("%d",f+i),(f[i] += ha) %= ha,(f[i] += ha) %= ha;
	FOR(i,0,k-1) scanf("%d",a+i),(a[i] += ha) %= ha,(a[i] += ha) %= ha;
	FOR(i,1,k) add(a[k],1ll*f[i]*a[k-i]%ha);
	Poly F;F.ext(k);F[k] = 1;
	FOR(i,1,k) F[k-i] = ha-f[i];
	Poly R;R.ext(0);R[0] = 1;
	Poly A;A.ext(1);A[1] = 1;n--;
	while(n){
		if(n & 1) R = R*A%F;
		A = A*A%F;n >>= 1;
	}
	int ans = 0;
	FOR(i,0,k-1) add(ans,1ll*a[i+1]*R[i]%ha);
	printf("%d\n",ans);
	return 0;
}
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

const int MAXN = 1e6 + 5;
const int ha = 786433;
const int G = 10;
const int Gn = 235930;
int n,q;

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
	inline void ext(int p){x.resize(p+1);}
	inline int& operator [](int p){return x[p];}
}A,B;

int r[MAXN],N;

inline void init(){
	N = 1ll<<18;
	FOR(i,1,N-1) r[i] = r[i>>1]>>1|((i&1)<<(18-1));
}

inline void NTT(Poly &A,int opt){
	A.ext(N);
	FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1;mid < N;mid <<= 1){
		int W = qpow(opt==-1?Gn:G,(ha-1)/(mid<<1));
		for(int i = 0;i < N;i += (mid<<1)){
			for(int w=1,j = 0;j < mid;++j,w = 1ll*w*W%ha){
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
int lg[ha+3],gl[ha+3];
int ans[MAXN];
int main(){
	scanf("%d",&n);A.ext(n);int sm = 0;
	FOR(i,0,n) scanf("%d",&A[i]);B = A;
	FOR(i,0,n) (sm += B[i]) %= ha;
	init();
	int now = 1;
	FOR(i,0,ha-1) lg[now] = i,gl[i] = now,now = 1ll*now*G%ha;
	NTT(A,1);
	FOR(i,0,N-1) ans[3*i] = A[i];
	A = B;
	now = 1;
	FOR(i,0,n) A[i] = 1ll*A[i]*now%ha,now = 1ll*now*G%ha;
	NTT(A,1);
	FOR(i,0,N-1) ans[3*i+1] = A[i];

	A = B;
	now = 1;
	FOR(i,0,n) A[i] = 1ll*A[i]*now%ha,now = 1ll*now*G%ha*G%ha;
	NTT(A,1);
	FOR(i,0,N-1) ans[3*i+2] = A[i];
	int q;scanf("%d",&q);
	while(q--){
		int x;scanf("%d",&x);
		if(x == 0){printf("%d\n",B[0]);continue;}
		if(x == 1){printf("%d\n",sm);continue;}
		printf("%d\n",ans[lg[x]]);
	}
	return 0;
}
/*
2
1 2 3
2
0
1
*/
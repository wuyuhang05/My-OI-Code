#include <algorithm>
#include <iostream>
#include <cstdio>
#include <queue>
#include <cmath>
#include <cstring>

#define fi first
#define se second
#define LL long long
#define P std::pair<int,int>
#define CLR(a,b) memset(a,b,sizeof(a))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl
#define int LL
const int MAXN = (1<<17)+2;
const double PI = acos(-1.0);
int ha,haha;

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct cp{
	double x,y;//x+iy
	cp(){x=0,y=0;}
	cp(long double x,long double y):x(x),y(y){}
	cp operator + (const cp &t) const {
		return cp(x+t.x,y+t.y);
	}
	cp operator - (const cp &t) const {
		return cp(x-t.x,y-t.y);
	}
	cp operator * (const cp &t) const {
		return cp(x*t.x-y*t.y,x*t.y+y*t.x);
	}
	LL D(){
		LL t = (x+0.499);
		return t%ha;
	}
};
int N,n,k;
int r[MAXN];

cp w[1<<17][100];

void init(){
    for(int i=2,j=0;j<17;j++,i<<=1){
        FOR(k,0,i-1) w[k][j] = cp(cos(2*PI*k/i),sin(2*PI*k/i));
    }
}

inline void FFT(cp *A,int limit,int opt){
	FOR(i,0,limit) if(i < r[i]) std::swap(A[i],A[r[i]]);
	for(int mid = 1,i=0;mid < limit;mid<<=1,++i){
        cp W(cos(PI/mid),sin(PI/mid));
		for(int j = 0;j < limit;j += (mid<<1)){
			cp w(1,0);
			for(int k = 0;k < mid;++k,w = w*W){
                w = ::w[k][i]; if(opt==-1) w.y=-w.y;
				cp x = A[j+k],y = w*A[j+mid+k];
				A[j+k] = x+y;A[j+mid+k] = x-y;
			}
		}
	}
	if(opt == -1){
		FOR(i,0,limit-1) A[i].x = A[i].x/limit;
	}
}

struct Poly{
	LL a[MAXN];

	Poly(){CLR(a,0);}
    
	friend Poly operator * (const Poly &a,const Poly &b){
		Poly ans;
		static cp A[MAXN],B[MAXN],C[MAXN],D[MAXN],E[MAXN],F[MAXN],G[MAXN];
		CLR(A,0);CLR(B,0);CLR(C,0);CLR(D,0);
		FOR(i,0,N-1) A[i].x = a.a[i]%haha,B[i].x = a.a[i]/haha;
		FOR(i,0,N-1) C[i].x = b.a[i]%haha,D[i].x = b.a[i]/haha;
		FFT(A,N,1);FFT(B,N,1);FFT(C,N,1);FFT(D,N,1);
		FOR(i,0,N-1){
			E[i] = A[i]*C[i];
			F[i] = A[i]*D[i]+B[i]*C[i];
			G[i] = B[i]*D[i];
		}
		FFT(E,N,-1);FFT(F,N,-1);FFT(G,N,-1);
		FOR(i,0,N-1) ans.a[i] = (E[i].D()%ha+F[i].D()%ha*haha%ha+G[i].D()%ha*haha%ha*haha%ha)%ha;
		FOR(i,k+1,N-1) ans.a[i] = 0;
		return ans;
	}
};

int inv[MAXN],fac[MAXN];

inline void pre(){
	fac[0] = 1;
	FOR(i,1,k) fac[i] = 1ll*fac[i-1]*i%ha;
	inv[k] = qpow(fac[k]);
	ROF(i,k-1,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    init();
}

Poly ans,f,f1,f2;

inline int C(int up,int down){
	return fac[up]*inv[down]%ha*inv[up-down]%ha;
}

signed main(){
    ha = 1e9+7;haha = 32768;
	scanf("%lld%lld%lld",&n,&k);--n;
    int len = 0;
    N = 1;pre();
    for(N=1;N<=(k*2);N<<=1,len++);
    FOR(i,0,N) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
	FOR(i,1,k) f.a[i] = 1;
    ans = f;
	LL now = 1;
	while(n){
		if(n & 1){
			f1 = ans;f2 = f;
			FOR(i,1,k) f1.a[i] = f1.a[i]*inv[i]%ha*qpow(qpow(2,i),now)%ha;
			FOR(i,1,k) f2.a[i] = f2.a[i]*inv[i]%ha;
			ans = f1*f2;
            FOR(i,1,k) if(ans.a[i]<0 && n == 29999) DEBUG(ans.a[i]);
			FOR(i,1,k) ans.a[i] = ans.a[i]*fac[i]%ha;
		}
		f1 = f2 = f;
		FOR(i,1,k) f1.a[i] = f1.a[i]*inv[i]%ha*qpow(qpow(2,i),now)%ha;
		FOR(i,1,k) f2.a[i] = f2.a[i]*inv[i]%ha;
		f = f1*f2;
		FOR(i,1,k) f.a[i] = f.a[i]*fac[i]%ha;
		n >>= 1;now <<= 1;
	}
	LL sum = 0;
	FOR(i,1,k) sum = (sum + ans.a[i]%ha*C(k,i)%ha)%ha;
	printf("%lld\n",sum);
	return 0;
}
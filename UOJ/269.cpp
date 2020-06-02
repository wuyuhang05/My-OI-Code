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

const int MAXN = 5e5 + 5;
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

inline void prework22(){
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
    A.ext(N);if(!W[0]) prework22();
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

int n,m,x;
int a[MAXN];
int fac[MAXN],inv[MAXN];

inline void prework(){
	fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
	inv[MAXN-1] = qpow(fac[MAXN-1]);
	ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

int main(){
	prework();
	scanf("%d%d%d",&n,&m,&x);
	FOR(i,0,m) scanf("%d",a+i);
	Poly A,B;A.ext(m);B.ext(m);
	FOR(i,0,m){
		A[i] = 1ll*a[i]*inv[i]%ha;
		B[i] = inv[i];if(i&1) B[i] = ha-B[i];
	}
	A = A*B;
	int tp = n,now = 1;
	int ans = 0,p = 1;
	FOR(i,0,m){
		(ans += 1ll*A[i]*p%ha*now%ha) %= ha;
		p  = 1ll*p*x%ha;
		if(tp > 0) now = 1ll*now*tp%ha;
		tp--;
	}
	printf("%d\n",ans);
	return 0;
}
#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

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

const int MAXN = 1e6 + 5;
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

namespace Polynomial{
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
			int W = opt==-1?(Polynomial::Wn[cnt]):(Polynomial::W[cnt]);
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
	
	Poly Dao(Poly A){
		Poly B;B.ext(A.deg()-1);
		FOR(i,1,A.deg()) B[i-1] = 1ll*A[i]*i%ha;
		return B;
	}
	
	Poly Int(Poly A){
		Poly B;B.ext(A.deg()+1);
		FOR(i,1,A.deg()+1) B[i] = 1ll*A[i-1]*qpow(i)%ha;
		Poly C = Dao(B);
		return B;
	}
	
	Poly Ln(Poly A){
		Poly res=Int(Dao(A)*Inv(A));
		res.ext(A.deg());
		return res;
	}
	
	Poly Exp(Poly A){
		Poly B;B.ext(0);B[0] = 1;int len;int n = A.deg();
		A.ext(n<<2);
		for(len = 1;len <= (n<<1);len <<= 1){
			B.ext(len);Poly C = Ln(B);
			FOR(i,0,len-1) C[i] = (A[i]+ha-C[i]+(i==0))%ha;
			B = B*C;
			B.ext(len-1);
		}
		B.ext(n);
		return B;
	}
}
using namespace Polynomial;

int n,k,s;
struct Edge{
    int to,nxt;
}e[MAXN];
int head[MAXN],cnt,w[MAXN];

inline void adde(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int num[MAXN];

inline void dfs(int v,int now=0){
    if(w[v]) now++;
    num[v] = now;
    for(int i = head[v];i;i = e[i].nxt) dfs(e[i].to,now);
}

int sz[MAXN],fac[MAXN],inv[MAXN];

inline int C(int n,int m){
    if(n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int main(){
    freopen("a.in","r",stdin);
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    read(n);read(k);read(s);
    FOR(i,2,n){
        int f;read(f);adde(f,i);
    }
    FOR(i,1,n) read(w[i]);
    dfs(1);
    FOR(i,1,n){
        if(w[i] || num[i] > 20) continue;
        sz[num[i]]++;
    }
    Poly P;P.ext(1);P[0] = 1;
    ROF(i,19,0){int lim=0;
        Poly t = P;P.x.clear();P.ext(lim=std::min(s,t.deg()*2));
        FOR(j,0,t.deg()) if(j*2 <= s) P[j*2] = t[j];
        t.x.clear();t.ext(std::min(lim,sz[i]));
        FOR(j,0,std::min(lim,sz[i])) t[j] = ((sz[i]-j)&1)?ha-C(sz[i],j):C(sz[i],j);
        P = P*t;P.ext(lim);
    }
    P.ext(s);
    Poly Q;Q.ext(s);
    FOR(i,0,s) if(1ll*i*(k+1) <= s) Q[i*(k+1)] = P[i];
    Q = Q*Inv(P);
    int res = 0;
    FOR(i,0,s) res ^= Q[i];//,DEBUG(Q[i]);
    printf("%d\n",res);
    return 0;
}

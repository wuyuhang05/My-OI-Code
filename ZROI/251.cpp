#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

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

const int ha = 998244353;
const int g = 3;
const int MAXN = 5e5 + 5;
const int ig = 332748118;

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
    inline int& operator [] (const int &n){return x[n];}
    inline void ext(int n){x.resize(n+1);}
    inline int deg(){return (int)x.size()-1;}
};

int r[MAXN],N;

inline void init(int n){
    int len = 0;N = 1;while(N <= n) N <<= 1,len++;
    FOR(i,0,N-1) r[i] = (r[i>>1]>>1)|((i&1)<<(len-1));
}

inline void NTT(Poly &A,int opt){
    A.ext(N);
    FOR(i,0,N-1) if(i < r[i]) std::swap(A[i],A[r[i]]);
    for(int mid = 1;mid < N;mid <<= 1){
        int W = qpow(opt==1?g:ig,(ha-1)/(mid<<1));
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

Poly operator * (Poly A,Poly B){
    int len = A.deg()+B.deg();init(len);
    NTT(A,1);NTT(B,1);
    FOR(i,0,N-1) A[i] = 1ll*A[i]*B[i]%ha;
    NTT(A,-1);A.ext(len);
    return A;
}

int n;
int inv[MAXN];
int main(){
    scanf("%d",&n);Poly f;f.ext(n-1);
    int fac = 1;
    FOR(i,0,n-1) scanf("%d",&f[i]),f[i] = 1ll*f[i]*fac%ha,fac = 1ll*fac*(i+1)%ha;
    Poly g = f*f;g.ext(2*n+3);
    int pw2 = 1,ifac = 1;
    inv[1] = 1;
    FOR(i,2,MAXN-1) inv[i] = 1ll*(ha-ha/i)*inv[ha%i]%ha;
    FOR(k,0,n-1){
        printf("%lld ",1ll*pw2*ifac%ha*g[n+k-1]%ha);
        ifac = 1ll*ifac*inv[k+1]%ha;
        pw2 = 2ll*pw2%ha;
    }
    puts("");
    return 0;
}

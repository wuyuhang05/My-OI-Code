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

const int MAXN = 3e5+5;
const int MAXM = 18+1;
const int ha = 1e9 + 7;
const int inv2 = (ha+1)/2;

int N;

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

inline void FMT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+mid+j] += f[i+j]) %= ha;
            }
        }
    }
}

inline void iFMT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                (f[i+mid+j] += ha-f[i+j]) %= ha;
            }
        }
    }
}

int f[MAXM][MAXN],g[MAXM][MAXN];
int n;
int pc[MAXN],tmp[MAXN];
bool p[MAXN];
int prime[MAXN],phi[MAXN],cnt;
int fac[MAXN];

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+(i&1),fac[i] = 1ll*fac[i-1]*i%ha;
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i,phi[i] = i-1;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;phi[i*prime[j]] = phi[i]*phi[prime[j]];
            if(!(i%prime[j])){
                phi[i*prime[j]] = phi[i]*prime[j];
                break;
            }
        }
    }
}

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}
int h[MAXN],F[MAXN];
int main(){
//    freopen("sequence.in","r",stdin);
//    freopen("sequence.out","w",stdout);
    prework();
    read(n);int mx = 0;
    int t0 = 1;
    FOR(i,1,n){
        int x;read(x);mx = std::max(mx,x);
        if(!x){
            t0 = 1ll*t0*2%ha;continue;
        }
        F[x]++;
    }
    N = 1;int len = 0;while(N <= mx) N <<= 1,len++;
    h[0] = 1;
#define lowbit(x) ((x)&(-(x)))
    FOR(S,1,N-1){
        for(int T = (S-1)&S;T;T=(T-1)&S){
            (h[S] += 1ll*h[T]*F[S-T]%ha) %= ha;
        }
        (h[S] += F[S]) %= ha;
    }
    int ans = t0;
    FOR(i,1,N-1) (ans += 1ll*h[i]*phi[i+1]%ha*t0%ha) %= ha;
    printf("%d\n",ans);
    return 0;
}
// 注意：多个 0

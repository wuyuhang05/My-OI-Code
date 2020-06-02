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

const int MAXN = 3e5 + 5;
const int MAXM = 18;
const int ha = 1e9 + 7;

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

int N = 262144,n = 18;

inline void FWT(int f[],int opt){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                if(opt == 1) (f[i+mid+j] += f[i+j]) %= ha;
                else (f[i+mid+j] += ha-f[i+j]) %= ha;
            }
        }
    }
}

int F[MAXM+1][MAXN],G[MAXM+1][MAXN],pc[MAXN];
bool p[MAXN];int prime[MAXN],cnt,phi[MAXN],inv[MAXN];

inline void prework(){
    FOR(i,1,MAXN-1) pc[i] = pc[i>>1]+(i&1);phi[1] = 1;
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
    inv[1] = 1;
    FOR(i,2,MAXN-1) inv[i] = 1ll*(ha-ha/i)*inv[ha%i]%ha;
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

inline void exp(){
    FOR(i,0,n) FWT(F[i],1);
    FOR(S,0,N-1){
        G[0][S] = 1;
        FOR(i,1,n){
            FOR(j,0,i-1){
                (G[i][S] += 1ll*(j+1)*F[j+1][S]%ha*G[i-1-j][S]%ha)%=ha;
            }
            G[i][S] = 1ll*G[i][S]*inv[i]%ha;
        }
    }
    FOR(i,0,n) FWT(G[i],-1);
}

int main(){prework();
    int m;read(m);int t0 = 1;
    while(m--){
        int x;read(x);
        if(x) F[pc[x]][x]++;
        else t0 = 2ll*t0%ha;
    }
    exp();int ans = 1;
    FOR(i,1,N-1) (ans += 1ll*G[pc[i]][i]*phi[i+1]%ha) %= ha;
    ans = 1ll*ans*t0%ha;
    printf("%d\n",ans);
    return 0;
}

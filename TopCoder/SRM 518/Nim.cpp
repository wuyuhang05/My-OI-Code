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
const int ha = 1000000007;
const int inv2 = 500000004;
bool p[MAXN];
int prime[MAXN],cnt;
inline void prework(){
    p[1] = 1;
    FOR(i,2,MAXN-1){
        if(!p[i]) prime[++cnt] = i;
        for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
            p[i*prime[j]] = 1;
            if(!(i%prime[j])) break;
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

int f[MAXN],N;

inline void FWT(int f[]){
    for(int mid = 1;mid < N;mid <<= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = (x+y)%ha;f[i+mid+j] = (x+ha-y)%ha;
            }
        }
    }
}

inline void iFWT(int f[]){
    for(int mid = N>>1;mid;mid >>= 1){
        for(int i = 0;i < N;i += (mid<<1)){
            FOR(j,0,mid-1){
                int x = f[i+j],y = f[i+mid+j];
                f[i+j] = 1ll*(x+y)%ha*inv2%ha;
                f[i+mid+j] = 1ll*(x+ha-y)%ha*inv2%ha;
            }
        }
    }
}

class Nim {
    public:
    int count(int K, int L) {
        prework();
        FOR(i,1,cnt){
            if(prime[i] > L) break;
            f[prime[i]] = 1;
        }
        N = 1;while(N <= L) N <<= 1;
        FWT(f);
        FOR(i,0,N-1) f[i] = qpow(f[i],K);
        iFWT(f);
        return f[0];
    }
};

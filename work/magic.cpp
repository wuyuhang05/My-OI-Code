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

const int MAXN = 100+5;
const int MAXM = 32;
int n,m,q;

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

std::bitset<MAXN> G[MAXN],w[MAXM+1][MAXN];

LL f[MAXN];

inline void prework(){
    FOR(t,1,MAXM){
        FOR(i,1,n){
            FOR(j,1,n){
                if(w[t-1][i][j]) w[t][i] ^= w[t-1][j];
            }
        }
    }
}
std::bitset<MAXN> A[MAXN],t[MAXN];
inline void mul(int p){
    FOR(i,1,n) t[i].reset();
    FOR(i,1,n){
        FOR(j,1,n){
            if(A[i][j]) t[i] ^= w[p][j];
        }
    }
    FOR(i,1,n) A[i] = t[i];
}

inline void qpow(LL n){
    FOR(i,1,::n) A[i].reset(),A[i][i] = 1;
    FOR(i,0,MAXM-1){
        if((n>>i)&1) mul(i);
    }
}

int main(){
    freopen("magic.in","r",stdin);
    freopen("magic.out","w",stdout);
    read(n);read(m);read(q);
    FOR(i,1,n) read(f[i]);
    FOR(i,1,m){
        int u,v;read(u);read(v);
        w[0][u][v] = w[0][v][u] = 1;
    }
    prework();
    FOR(i,1,q){
        LL x;read(x);qpow(x);LL res = 0;
        FOR(j,1,n) res ^= f[j]*A[j][1];
        printf("%lld\n",res);
    }
    return 0;
}



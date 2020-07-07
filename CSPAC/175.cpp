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

const int MAXN = 1e5 + 5;
const int MAXM = 16;

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

struct Poly{
    std::vector<int> x; 
    inline int deg(){return (int)x.size()-1;}
    inline void ext(const int &n){x.resize(n+1);}
    inline int& operator [](const int &n){return x[n];}

    inline void print(){
        for(auto val:x) printf("%d ",val);
        puts("");
    }
};

const int ha = 998244353;

inline int qpow(int a,int n=ha-2){
    if(a == 1) return a;
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void add(int &x,LL y){
    (x += y);if(x >= ha) x -= ha;
}

inline Poly operator * (Poly &A,Poly &B){
    Poly C;C.ext(A.deg()+B.deg());
    FOR(i,0,A.deg()) FOR(j,0,B.deg()) add(C[i+j],1ll*A[i]*B[j]%ha);
    return C;
}

inline Poly operator / (Poly &A,Poly &B){// 除二项式
    Poly C;C.ext(A.deg()-1);
    int inv = qpow(B[0]);
    C[0] = 1ll*A[0]*inv%ha;
    FOR(i,1,A.deg()-1){
        C[i] = A[i];
        add(C[i],ha-1ll*B[1]*C[i-1]%ha);
        C[i] = 1ll*C[i]*inv%ha;
    }
    return C;
}

int n,q;

struct Edge{
    int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void adde(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int sz[MAXN],dep[MAXN],dfn[MAXN];
int fac[MAXN],inv[MAXN];
Poly p[MAXN];
int f[MAXN][MAXM+1];

void dfs(int v,int fa=0){
    static int ts = 0;dfn[v] = ++ts;
    sz[v] = 1;p[v].ext(0);p[v][0] = 1;dep[v] = dep[fa]+1;
    Poly t;t.ext(1);t[0] = 1;
    f[v][0] = fa;
    FOR(i,1,MAXM) f[v][i] = f[f[v][i-1]][i-1];
    for(int i = head[v];i;i = e[i].nxt){
        if(e[i].to == fa) continue;
        dfs(e[i].to,v);
        sz[v] += sz[e[i].to];
        t[1] = sz[e[i].to];
        p[v] = p[v]*t;
    }
    t[1] = n-sz[v];
    p[v] = p[v]*t;
}

inline int jump(int x,int k){
    FOR(i,0,MAXM) if((k>>i)&1) x = f[x][i];
    return x;
}

int main(){
//    freopen("A.in","r",stdin);
//    freopen("A.out","w",stdout);
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
    read(n);read(q);
    FOR(i,2,n){
        int u,v;read(u);read(v);
        adde(u,v);
    }
    dfs(1);
    FOR(i,1,q){
        int u,v,k,opt;read(u);read(v);read(k);read(opt);
        if(dep[u] > dep[v]) std::swap(u,v);
        Poly A=p[u],B=p[v];
        Poly t;t.ext(1);t[0] = 1;
        if(!(dfn[v] >= dfn[u] && dfn[v] <= dfn[u]+sz[u]-1)){
            t[1] = n-sz[u];
            A = A/t;
            t[1] = n-sz[v];
            B = B/t;
        }
        else{
            int ps = jump(v,dep[v]-dep[u]-1);
//            for(int i = head[u];i;i = e[i].nxt){
//                if(dfn[e[i].to] <= dfn[v] && dfn[v] <= dfn[e[i].to]+sz[e[i].to]-1){ps = e[i].to;break;}
//            }
            t[1] = sz[ps];
            A = A/t;
            t[1] = n-sz[v];
            B = B/t;
        }
        int ans1=0,ans2=0;
        A.ext(k);B.ext(k);
        if(opt == 0){
            FOR(i,0,k){
                add(ans1,1ll*A[i]*inv[k-i]%ha);
                add(ans2,1ll*B[i]*inv[k-i]%ha);
            }
            ans1 = 1ll*ans1*fac[k]%ha;
            ans2 = 1ll*ans2*fac[k]%ha;
        }
        else{
            t[1] = 1;
            A = A*t;B = B*t;
            ans1 = 1ll*A[k]*fac[k]%ha;ans2 = 1ll*B[k]*fac[k]%ha;
        }
        printf("%lld\n",1ll*ans1*ans2%ha);
    }
    return 0;
}

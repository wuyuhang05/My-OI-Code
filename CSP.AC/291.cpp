#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

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
const int MAXK = 500 + 5;
const int ha = 998244353;

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

struct Edge{
    int to,nxt;
}e[MAXN<<1];
bool vis[MAXN];
int head[MAXN],cnt,deg[MAXN];

inline void adde(int u,int v){
    e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
    deg[v]++;
}

inline void add(int &x,int y){
    (x += y);if(x >= ha) x -= ha;
}

int f[MAXN][MAXK];
int n,m,k;
int fac[MAXN],inv[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

inline void prework(){
    fac[0] = 1;FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
    inv[MAXN-1] = qpow(fac[MAXN-1]);
    ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
    if(n < 0 || m < 0 || n < m) return 0;
    return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}

int g[MAXK][MAXK];
// i个变量,和为 j

int main(){
    prework();
    read(n);read(m);read(k);
    g[0][0] = 1;
    FOR(i,1,k){
        FOR(j,i,k){
            FOR(x,1,j){
                add(g[i][j],1ll*g[i-1][j-x]*C(k-(j-x),x)%ha);
            }
        }
    }
    FOR(i,1,m){
        int u,v;read(u);read(v);
        adde(u,v);
    }
    std::queue<int> q;
    q.push(1);vis[1] = 1;
    while(!q.empty()){
        int v = q.front();q.pop();
        for(int i = head[v];i;i = e[i].nxt){
            if(vis[e[i].to]) continue;
            q.push(e[i].to);vis[e[i].to] = 1;
        }
    }
    FOR(v,1,n){
        if(!vis[v]){
            for(int i = head[v];i;i = e[i].nxt){
                deg[e[i].to]--;
            }
        }
    }
    q.push(1);
    f[1][0] = 1;
//    assert(deg[1]==0);
    FOR(i,1,n) vis[i] = 0;
    while(!q.empty()){
        int v = q.front();q.pop();vis[v] = 1;
        for(int i = head[v];i;i = e[i].nxt){
            FOR(x,0,k){
                if(!f[v][x]) continue;
                FOR(y,0,std::min(1,k-x)){
                    add(f[e[i].to][x+y],f[v][x]);
                }
            }
            if(!--deg[e[i].to]) q.push(e[i].to);
        }
    }
    FOR(i,1,n){
        int ans = 0;
        FOR(j,1,k){
            add(ans,1ll*f[i][j]*g[j][k]%ha);
        }
        printf("%d\n",ans);
    }
    return 0;
}
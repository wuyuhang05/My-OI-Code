#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

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


const int MAXN = 1e5 + 5;
const int ha = 998244353;
bool p[MAXN];
int prime[MAXN],cnt;
int g[MAXN],rg[MAXN],sz[MAXN];

inline void prework(){
	FOR(i,2,MAXN-1){
		if(!p[i]) prime[++cnt] = i,rg[i] = cnt;
		for(int j = 1;j <= cnt && i*prime[j] < MAXN;++j){
			p[i*prime[j]] = 1;
			if(!(i%prime[j])) break;
		}
	}
	FOR(i,1,cnt){
		for(LL j = prime[i];j < MAXN;j *= prime[i]){
			g[j] = prime[i];
		}
	}
}

int a[MAXN];
int LIM=std::sqrt(100000.0),BLO;
std::vector<P> dec[MAXN];int ext[MAXN];

inline void fj(int id){
	int x = a[id],q = std::sqrt(1.0*x);
	FOR(i,1,cnt){
		if(prime[i] > x || prime[i] > q) break;
		if(!(x%prime[i])){
			int t = 0;
			while(!(x%prime[i])) x /= prime[i],++t;
			dec[id].pb(MP(prime[i],t));
		}
	}
	ext[id] = -1;
	if(x != 1){
		if(x >= LIM){
			ext[id] = x;sz[x]++;
		}
		else{
			dec[id].pb(MP(x,1));
		}
	}
}

int n,m;
int ans[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}

struct Node{
	int l,r,id;
	Node(int l=0,int r=0,int id=0) : l(l),r(r),id(id) {}
	bool operator < (const Node &t) const{
		if(l/BLO != t.l/BLO) return l < t.l;
		if((l/BLO)&1) return r < t.r;
		return r > t.r;
	}
}qry[MAXN];

bool wk[MAXN];
int sm[MAXN],pw[MAXN];int nowans = 1;
int tt[MAXN];
int *pwp[MAXN],*qwq[MAXN];
int pool[20000000+3],*tail=pool;

inline void add(int id,int d){
	if(ext[id] == -1) return;
	int t = tt[ext[id]];
	tt[ext[id]] += d;
	nowans = 1ll*nowans*(d==1?pwp:qwq)[ext[id]][d==1?t:t-1]%ha;
}

int main(){
	freopen("C2.in","r",stdin);
	freopen("a.ans","w",stdout);
	prework();
	read(n);read(m);
	FOR(i,1,n) read(a[i]),fj(i);BLO = std::sqrt(m);
	FOR(i,LIM,MAXN-1){
		if(p[i]) continue;
		pwp[i] = tail;tail += sz[i]+2;
		qwq[i] = tail;tail += sz[i]+2;
		pwp[i][0] = i;qwq[i][0] = qpow(i);
		FOR(j,1,sz[i]+1) pwp[i][j] = 1ll*pwp[i][j-1]*pwp[i][j-1]%ha,
		qwq[i][j] = 1ll*qwq[i][j-1]*qwq[i][j-1]%ha;
	}
	FOR(i,1,m){
		int l,r;read(l);read(r);
		qry[i] = Node(l,r,i);ans[i] = 1;
	}
	FOR(i,1,n){
		for(auto x:dec[i]){
			int now = x.fi;
			FOR(j,1,x.se){
				wk[now] = 1;
				now *= x.fi;
			}
		}
	}
	FOR(i,1,MAXN-1){
		if(!wk[i]) continue;
		int p = g[i],invp = qpow(p);
		pw[0] = p;
		FOR(j,1,n){
			if(a[j]%i) sm[j] = 0;
			else sm[j] = 1;
			sm[j] += sm[j-1];
			pw[j] = 1ll*pw[j-1]*pw[j-1]%ha;
		}
		FOR(j,1,m){
			int t = pw[sm[qry[j].r]-sm[qry[j].l-1]];
			t--;while(t < 0) t += ha-1;t %= (ha-1);
			ans[qry[j].id] = 1ll*ans[qry[j].id]*pw[sm[qry[j].r]-sm[qry[j].l-1]]%ha*invp%ha;
		}
	}
	std::sort(qry+1,qry+m+1);
	int L = qry[1].l,R = qry[1].r;
	FOR(i,L,R) add(i,1);ans[qry[1].id] = 1ll*ans[qry[1].id]*nowans%ha;
	FOR(i,2,m){
		int l = qry[i].l,r = qry[i].r;
		while(l < L) add(--L,1);
		while(R < r) add(++R,1);
		while(L < l) add(L++,-1);
		while(r < R) add(R--,-1);
		ans[qry[i].id] = 1ll*ans[qry[i].id]*nowans%ha;
	}
	FOR(i,1,m) printf("%d\n",ans[i]);
	return 0;
}
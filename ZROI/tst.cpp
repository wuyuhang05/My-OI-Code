#pragma GCC optimize("Ofast")
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
const int ha = 998244353;
int pw[MAXN];
std::vector<P> dec[MAXN];
int prime[MAXN],cnt;
bool p[MAXN];

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

inline void prework(){
	pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 2ll*pw[i-1]%(ha-1);
	// FOR(i,0,MAXN-1) (pw[i] += ha-1) %= ha;
	FOR(i,2,MAXN-1){
		if(!p[i]) prime[++cnt] = i;
		for(int j = 1;j < cnt && i*prime[j] < MAXN;++j){
			p[i*prime[j]] = 1;
			if(!(i%prime[j])) break;
		}
	}
}

int a[MAXN];
inline void fj(int x,int id){
	int q = std::sqrt(1.0*x);
	FOR(i,1,cnt){
		if(prime[i] > q || prime[i] > x) break;
		if(!(x%prime[i])){
			int t = 0;
			while(!(x%prime[i])) x /= prime[i],t++;
			dec[id].pb(MP(prime[i],t));
		}
	}
	if(x != 1) dec[id].pb(MP(x,1));
}

int tt[MAXN],nowans=1;
int ans[MAXN],ttt[MAXN];

inline int qpow(int a,int n=ha-2,int mod=ha){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%mod;
		a = 1ll*a*a%mod;
		n >>= 1;
	}
	return res;
}

inline void add(int id,int d){
	for(auto x:dec[id]){
		int now = x.fi;
		LL delta = 0;
		FOR(i,1,x.se){
			if(now >= 317){
			int t = tt[now];
			DEBUG(now);
			if(d == 1) (delta += pw[t]+ha-1) %= (ha-1);
			else (delta += pw[t-1]-pw[t]+(ha-1)) %= (ha-1);
			tt[now] += d;}
			now = now*x.fi;
		}
		nowans = 1ll*nowans*qpow(x.fi,(delta+ha-1)%(ha-1))%ha;
	}
}

int n,q;
int BLO;
struct Node{
	int l,r,id;
	Node(int l=0,int r=0,int id=0) : l(l),r(r),id(id) {}
	inline bool operator < (const Node &t) const {
    	if(l/BLO!=t.l/BLO) return l<t.l;
    	if((l/BLO) & 1) return r<t.r;
    	else return r>t.r;
    }
}qry[MAXN];

int main(){
	freopen("b.in","r",stdin);
	// freopen("c.out","w",stdout);
	prework();
	read(n);read(q);
	// int LG = 1.0*log(q)/log(2);
	BLO = std::sqrt(1.0*q);
	// DEBUG(q);
	FOR(i,1,n) read(a[i]),fj(a[i],i);
	FOR(i,1,q){
		int l,r;read(l);read(r);
		qry[i] = Node(l,r,i);
	}
	std::sort(qry+1,qry+q+1);
	int L = qry[1].l,R = qry[1].r;
	FOR(i,L,R) add(i,1);
	ans[qry[1].id] = nowans;
	// DEBUG(L);DEBUG(R);
	// DEBUG(nowans);
	// exit(0);
	FOR(i,2,q){
		// DEBUG(i);
		int l = qry[i].l,r = qry[i].r;
		while(R < r) add(++R,1);
		while(l < L) add(--L,1);
		while(r < R) add(R--,-1);
		while(L < l) add(L++,-1);
		ans[qry[i].id] = nowans;
	}
	FOR(i,1,MAXN){
		if(tt[i]) printf("%d %d\n",i,tt[i]);
	}
	FOR(i,1,q) printf("%d\n",ans[i]);
	// DEBUG(1ll*121211013*qpow(237155644)%ha);
	return 0;
}
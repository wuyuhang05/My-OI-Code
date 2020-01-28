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
#define P std::pair
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 1e5 + 5;
const int MAXM = 15;

struct LCT{
	#define lc (ch[x][0])
	#define rc (ch[x][1])
	int ch[MAXN][2],f[MAXN],rev[MAXN];

	struct Node{
		double a[MAXM+1];

		inline Node operator + (const Node &t) const {
			Node res;
			FOR(i,0,MAXM) res.a[i] = a[i]+t.a[i];
			return res;
		}
	}sm[MAXN],val[MAXN];

	inline bool nroot(int x){
		return x == ch[f[x]][0] || x == ch[f[x]][1];
	}

	inline void pushup(int x){
		sm[x] = sm[lc]+sm[rc]+val[x];
	}

	inline void reverse(int x){
		std::swap(lc,rc);rev[x] ^= 1;
	}

	inline void pushdown(int x){
		if(rev[x]){
			if(lc) reverse(lc);
			if(rc) reverse(rc);
			rev[x] = 0;
		}
	}

	inline void rotate(int x){
		int y = f[x],z = f[y],k = ch[y][1] == x,w = ch[x][!k];
		if(nroot(y)) ch[z][ch[z][1] == y] = x;
		ch[x][!k] = y;ch[y][k] = w;
		if(w) f[w] = y;f[y] = x;f[x] = z;
		pushup(y);
	}

	int st[MAXN];
	inline void splay(int x){
		int y = x,z;
		st[z = 1] = y;
		while(nroot(y)) st[++z] = y = f[y];
		while(z) pushdown(st[z--]);
		while(nroot(x)){
			y = f[x],z = f[y];
			if(nroot(y)) rotate((ch[y][1]==x)^(ch[z][1]==y) ? x : y);
			rotate(x);
		}
		pushup(x);
	}

	inline void access(int x){
		for(int y=0;x;x = f[y = x]){
			splay(x);rc = y;pushup(x);
		}
	}

	inline void makeroot(int x){
		access(x);splay(x);reverse(x);
	}

	inline void split(int x,int y){
		makeroot(x);access(y);splay(y);
	}

	inline void link(int x,int y){
		makeroot(x);makeroot(y);f[y] = x;
	}

	inline void cut(int x,int y){
		split(x,y);f[x] = ch[y][0] = 0;pushup(y);
	}

	inline int findroot(int x){
		access(x);splay(x);
		while(lc) pushdown(x),x = lc;
		splay(x);
		return x;
	}

	inline bool connect(int x,int y){
		return findroot(x) == findroot(y);
	}

	inline Node query(int x,int y){
		split(x,y);
		return sm[y];
	}

	inline void update(int x){
		int t = x;
		while(nroot(x)) pushup(x = f[x]);
		splay(t);
	}
}T;

int n,m;
double res[MAXN];
int fac[MAXN];

inline void Taylor(int f,double a,double b){
	if(f == 1){
		double t = 1;
		FOR(i,0,MAXM){
			if(i%4 <= 1){
				if(i&1) res[i] = t*cos(b);
				else res[i] = t*sin(b);
			}
			else{
				if(i&1) res[i] = -t*cos(b);
				else res[i] = -t*sin(b);
			}
			res[i] = 1.0*res[i]/fac[i];
			t *= a;
		}
	}
	if(f == 2){
		double t = exp(b);
		FOR(i,0,MAXM){
			res[i] = 1.0*t/fac[i];
			t *= a;
		}
	}
	if(f == 3){
		res[0] = b;res[1] = a;
		FOR(i,2,MAXM) res[i] = 0;
	}
}

char str[233];

int main(){
	// freopen("b2.in","r",stdin);
	// freopen("b2.out","w",stdout);
	fac[0] = 1;
	FOR(i,1,MAXM) fac[i] = fac[i-1]*i;
	scanf("%d%d%*s",&n,&m);
	FOR(i,1,n){
		int f;double a,b;scanf("%d%lf%lf",&f,&a,&b);
		Taylor(f,a,b);
		FOR(j,0,MAXM) T.val[i].a[j] = res[j];
	}
	FOR(i,1,m){
		// DEBUG(i);
		scanf("%s",str+1);
		if(str[1] == 'a'){
			int u,v;scanf("%d%d",&u,&v);++u;++v;
			T.link(u,v); 
		}
		if(str[1] == 'd'){
			int u,v;scanf("%d%d",&u,&v);++u;++v;
			T.cut(u,v);
		}
		if(str[1] == 'm'){
			int v,f;double a,b;
			scanf("%d%d%lf%lf",&v,&f,&a,&b);++v;
			Taylor(f,a,b);
			FOR(i,0,MAXM) T.val[v].a[i] = res[i];
			T.update(v);
		}
		if(str[1] == 't'){
			int u,v;double x;scanf("%d%d%lf",&u,&v,&x);++u;++v;
			if(!T.connect(u,v)) puts("unreachable");
			else{
				double res = 0,t = 1;
				LCT::Node abc = T.query(u,v);
				FOR(i,0,MAXM) res += t*abc.a[i],t *= x;
				printf("%.8e\n",res);
			}
			// FOR(i,0,MAXN)
		}
		// DEBUG(i);
	}
	return 0;
}
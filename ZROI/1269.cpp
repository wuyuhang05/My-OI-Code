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

const int MAXN = 30000+5;
const int ha = 998244353;

inline char nc(){
    #define SIZE 1000000+3
    static char buf[SIZE],*p1 = buf+SIZE,*p2 = buf+SIZE;
    if(p1 == p2){
        p1 = buf;p2 = buf+fread(buf,1,SIZE,stdin);
        if(p1 == p2) return -1;
    }
    return *p1++;
}
 
inline void read(int &x){
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

inline void add(int &x,int y){
	(x += y);if(x < 0) x += ha;
	if(x >= ha) x -= ha;
}

struct Node{
	int a[2][2];
	Node(){CLR(a,0);FOR(i,0,1) a[i][i] = 1;}

	Node operator * (const Node &t) const {
		Node res;CLR(res.a,0);
		FOR(i,0,1){
			FOR(j,0,1){
				add(res.a[i][j],1ll*a[i][0]*t.a[0][j]%ha);
				add(res.a[i][j],1ll*a[i][1]*t.a[1][j]%ha);
			}
		}
		return res;
	}

	inline void print(){
		FOR(i,0,1) FOR(j,0,1) printf("%d%c",a[i][j]," \n"[j==1]);
	}
};
int N;
#define lc ((x)<<1)
#define rc ((x)<<1|1)

struct DS{
	Node sm[MAXN<<2];
	inline void build(){
		ROF(x,N-1,0) sm[x] = sm[lc]*sm[rc];
	}

	inline void update(int x,const Node &d){
		sm[x+=N] = d;
		for(x>>=1;x;x >>= 1) sm[x] = sm[lc]*sm[rc];
	}
}SEG[28];

int n,q,lim[MAXN],pw[MAXN],ipw[MAXN];

inline int qpow(int a,int n=ha-2){
	int res = 1;
	while(n){
		if(n & 1) res = 1ll*res*a%ha;
		a = 1ll*a*a%ha;
		n >>= 1;
	}
	return res;
}
int sm[28];
int main(){
	// freopen("A.in","r",stdin);
	// freopen("A.out","w",stdout);DEBUG(1);
	read(n);read(q);
	FOR(i,1,n) read(lim[i]);pw[0] = 1;
	FOR(i,1,30) pw[i] = 1ll*pw[i-1]*2%ha;
	ipw[30] = qpow(pw[30]);
	ROF(i,29,0) ipw[i] = ipw[i+1]*2ll%ha;
	N = 1;while(N <= n) N <<= 1;
	ROF(k,27,0){
		FOR(i,1,n){
			Node t;CLR(t.a,0);
			int d = (lim[i]&((1<<k)-1))+1,x = pw[k]; 
			if((lim[i]>>k)&1){
				t.a[0][0] = t.a[1][1] = x;
				t.a[0][1] = t.a[1][0] = d;
			}
			else t.a[0][0] = t.a[1][1] = d;
			SEG[k].sm[i+N] = t;
			if(i == 1) sm[k] = d;
			else sm[k] = 1ll*sm[k]*d%ha;
			// sm[k][i+N] = t;
			// tmp[i] = t;
		}
		SEG[k].build();
	}
	int now = 0;FOR(i,1,n) now ^= lim[i];
	FOR(i,1,q){
		int x,y;read(x);read(y);
		int rd = lim[x];
		now ^= lim[x];lim[x] = y;now ^= lim[x];
		int ans = 0;//DEBUG(i);
		ROF(k,27,0){
			Node t;CLR(t.a,0);
			int d = (lim[x]&((1<<k)-1))+1,xx = pw[k];
			if((lim[x]>>k)&1){
				t.a[0][0] = t.a[1][1] = xx;
				t.a[0][1] = t.a[1][0] = d;
			}
			else t.a[0][0] = t.a[1][1] = d;
			SEG[k].update(x,t);
			sm[k] = 1ll*sm[k]*qpow((rd&((1<<k)-1))+1)%ha;
			sm[k] = 1ll*sm[k]*((lim[x]&((1<<k)-1))+1)%ha;
			// update(k,x,t);
			int res = SEG[k].sm[1].a[((now>>k)&1)][0];
			add(res,ha-sm[k]);
			// if(k <= 1) SEG[k].sm[1].print();
			res = 1ll*res*ipw[k]%ha;
			add(ans,res);
			// add(ans,1ll*ipw[k]*SEG[k].sm[1].a[((now>>k)&1) ? 3 : 1][0]%ha);
			// add(ans,1ll*ipw[k]*sm[k][1].a[((now>>k)&1) ? 3 : 1][0]%ha);
		}
		add(ans,1);
		printf("%d\n",ans);
	}
	return 0;
}
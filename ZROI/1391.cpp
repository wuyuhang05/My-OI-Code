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

const int MAXN = 2e5 + 5;
const int ha = 998244353; 
int a[MAXN];
int n,q;

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
	fac[0] = 1;
	FOR(i,1,MAXN-1) fac[i] = 1ll*fac[i-1]*i%ha;
	inv[MAXN-1] = qpow(fac[MAXN-1]);
	ROF(i,MAXN-2,0) inv[i] = 1ll*inv[i+1]*(i+1)%ha;
}

inline int C(int n,int m){
	if(n < m) return 0;
	if(!m) return 1;
	return 1ll*fac[n]*inv[m]%ha*inv[n-m]%ha;
}
int sm[MAXN];
const int inv2=(ha+1)/2;
int pw[MAXN];

std::vector<std::pair<std::vector<int>,int> > qry[MAXN];
int sm1[MAXN],ans[MAXN];
int main(){
	prework();
	read(n);read(q);int all = 0;
	pw[0] = 1;FOR(i,1,MAXN-1) pw[i] = 1ll*pw[i-1]*inv2%ha;
	FOR(orz_sddz_scb,1,q){
		int k;read(k);std::vector<int> tmp;
		FOR(i,1,k){
			int x;read(x);tmp.pb(x);
		}
		qry[k].pb(MP(tmp,orz_sddz_scb));
	}
	FOR(k,1,n){
		if(qry[k].empty()) continue;
		FOR(i,0,n-1) sm[i] = 0;
		FOR(i,n,2*n-1) sm[i] = (sm[i-1]+1ll*pw[i]*C(i-k-1,i-n)%ha)%ha;
		FOR(i,0,2*n) sm1[i] = (i==0?0:sm1[i-1]+1ll*pw[i]*C(i-1,n-1)%ha)%ha;
		for(auto x:qry[k]){
			int id = x.se;
			std::vector<int> tmp = x.fi;int mx = 0;
			for(auto x:tmp) mx = std::max(mx,x);
			// 同色
			for(auto x:tmp)
				if(x >= mx && x >= n && x <= 2*n-1) (ans[id] += 1ll*pw[x]*C(x-k,x-n)%ha)%=ha;
			int lst = mx;
			for(auto x:tmp){
				if(x < n || x < mx) continue;
				if(x != lst) (ans[id] += (sm[x-1]+ha-sm[lst])%ha) %= ha;
				lst = x;
			}
			if(2*n-1 >= mx) (ans[id] += (sm[2*n-1]+ha-sm[lst])%ha) %= ha;
			// 异色
			lst = n-1;int ts = 0;
			for(auto x:tmp){
				if(x < n) {++ts;continue;}
				if(lst+1 <= x-1){
					int t = (sm1[x-1-ts]+ha-sm1[lst-ts])%ha;
					t = 1ll*t*pw[ts]%ha;
					(ans[id] += t) %= ha;
				}
				lst = x;
				++ts;
			}
			if(lst+1 <= 2*n-1){
				int t = (sm1[2*n-1-ts]+ha-sm1[lst-ts])%ha;
				t = 1ll*t*pw[ts]%ha;
				(ans[id] += t) %= ha;
			}
			ans[id] = 2ll*ans[id]%ha;
		}
	}
	FOR(i,1,q) printf("%d\n",ans[i]);
	return 0;
}
/*
O(qnk)
枚举在哪里停下来 组合数计算一下
*/
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

const int ha = 1e9 + 7;
const int MAXN = 1e6 + 5;

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

struct BIT{
	int sm[MAXN],smi[MAXN];
	#define lb(x) ((x)&(-(x)))
	inline void add(int pos,int d){
		int t = pos;
		for(;pos<MAXN;pos+=lb(pos)){
			(sm[pos] += d) %= ha;
			(smi[pos] += 1ll*d*t%ha) %= ha;
		}
	}
	
	inline void modify(int l,int r,int d){
		add(l,d);add(r+1,ha-d);
	}

	inline int qry(int pos){
		int res = 0,t = pos;
		for(;pos;pos-=lb(pos)) (res += (1ll*(t+1)*sm[pos]%ha+ha-smi[pos])%ha) %= ha;
		return res;
	}
	
	inline int query(int l,int r){
		return (qry(r)+ha-qry(l-1))%ha;
	}
	#undef lb
}bit;

int a[MAXN],pre[MAXN];
std::map<int,int> S;
int main(){
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
	int n;read(n);
	FOR(i,1,n){
		read(a[i]);
		pre[i] = S[a[i]];S[a[i]] = i;
	}
	int ans = 0,now = 0;
	FOR(i,1,n){
		int l = pre[i]+1,r = i;
		(now += (r-l+1))%=ha;
		(now += 2ll*bit.query(l,r)%ha)%=ha;
		bit.modify(l,r,1);
		(ans += now)%=ha;
	}
	printf("%d\n",ans);
	return 0;
}
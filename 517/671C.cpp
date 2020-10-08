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

LL ha,a[MAXN],phi;
int n,q;

inline LL gcd(LL a,LL b){
	return !b ? a : gcd(b,a%b);
}

inline LL mul(LL a,LL b,LL p=ha){
	return (a*b-(LL)((long double)a*b/p)*p+p)%p;
}

LL sm[MAXN<<2],lcm[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
	sm[x] = mul(sm[lc],sm[rc]);
	lcm[x] = lcm[lc]/gcd(lcm[lc],lcm[rc])*lcm[rc];// ord <= p-1
}

std::vector<LL> dec;

inline LL qpow(LL a,LL n=ha-2){
	LL res = 1;
	while(n){
		if(n & 1) res = mul(res,a);
		a = mul(a,a);
		n >>= 1;
	}
	return res;
}

inline LL ord(LL x){
	LL res = ha-1;
	for(auto v:dec) while(!(res%v) && qpow(x,res/v) == 1) res /= v;
	return res;
}

inline void build(int x,int l,int r){
	if(l == r){
		sm[x] = mul(a[l],qpow(a[l-1]));
		lcm[x] = ord(sm[x]);		
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

inline void update(int x,int l,int r,int p,LL d){
	if(l == r){
		sm[x] = mul(sm[x],d);
		lcm[x] = ord(sm[x]);
		return;
	}
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc,l,mid,p,d);
	else update(rc,mid+1,r,p,d);
	pushup(x);
}

inline LL query1(int x,int l,int r,int L,int R){
	if(L > R) return 1;
	if(l == L && r == R) return sm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query1(lc,l,mid,L,R);
	if(L > mid) return query1(rc,mid+1,r,L,R);
	return mul(query1(lc,l,mid,L,mid),query1(rc,mid+1,r,mid+1,R));
}

inline LL query2(int x,int l,int r,int L,int R){
	if(L > R) return 1;
	if(l == L && r == R) return lcm[x];
	int mid = (l + r) >> 1;
	if(R <= mid) return query2(lc,l,mid,L,R);
	if(L > mid) return query2(rc,mid+1,r,L,R);
	LL ls = query2(lc,l,mid,L,mid),rs = query2(rc,mid+1,r,mid+1,R);
	return ls/gcd(ls,rs)*rs;
}

inline void fj(LL x){
	int q = std::sqrt(1.0*x);
	FOR(i,2,q){
		if(!(x%i)){
			dec.pb(i);
			while(!(x%i)) x /= i;
		}
	}
	if(x != 1) dec.pb(x);
}

int main(){
	scanf("%lld%d%d",&ha,&n,&q);
	FOR(i,1,n) scanf("%lld",a+i);fj(ha-1);a[0] = 1;
	build(1,1,n);
	FOR(i,1,q){
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);
		if(opt == 1){
			LL x;scanf("%lld",&x);
			update(1,1,n,l,x);
			if(r < n) update(1,1,n,r+1,qpow(x));
		}
		else{
			LL res = query2(1,1,n,l+1,r),v = query1(1,1,n,1,l);v = ord(v);
			res = res/gcd(res,v)*v;
			printf("%lld\n",res);
		}
	}
	return 0;
}
/*
17 3 7
10 16 2
2 2 3
2 1 2
2 2 2
1 1 2 3
2 1 1
2 3 3
2 1 3
*/
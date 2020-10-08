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

const int MAXN = 2e5 + 5;

LL sm1[MAXN<<2],sm2[MAXN<<2],coe1[MAXN<<2],coe2[MAXN<<2];
LL tag[MAXN<<2],clr[MAXN<<2];
// 1: 鏁伴噺 2: 鑺辫垂

LL c[MAXN];
P a[MAXN];
int n,m;

#define lc ((x)<<1)
#define rc ((x)<<1|1)

inline void pushup(int x){
	sm1[x] = sm1[lc]+sm1[rc];
	sm2[x] = sm2[lc]+sm2[rc];
	coe1[x] = coe1[lc]+coe1[rc];
	coe2[x] = coe2[lc]+coe2[rc];
}

inline void build(int x,int l,int r){
	if(l == r){
		sm1[x] = sm2[x] = 0;
		coe1[x] = a[l].se;coe2[x] = 1ll*a[l].fi*a[l].se;
		return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

inline void cover(int x,LL d){
	sm1[x] += coe1[x]*d;
	sm2[x] += coe2[x]*d;
	tag[x] += d;
}

inline void reset(int x){
	sm1[x] = sm2[x] = tag[x] = 0;clr[x] = 1;
}

inline void pushdown(int x){
	if(clr[x]){
		reset(lc);
		reset(rc);
		clr[x] = 0;//tag[x] = 0;
	}
	if(tag[x]){
		cover(lc,tag[x]);
		cover(rc,tag[x]);
		tag[x] = 0;
	}
}

inline void modify(int x,int l,int r,int L,int R){
	if(L > R) return;
	if(l == L && r == R){
		reset(x);
		return;
	}
	int mid = (l + r) >> 1;pushdown(x);
	if(R <= mid) modify(lc,l,mid,L,R);
	else if(L > mid) modify(rc,mid+1,r,L,R);
	else modify(lc,l,mid,L,mid),modify(rc,mid+1,r,mid+1,R);
	pushup(x);
}

inline LL query1(int x,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l == L && r == R) return sm1[x];
	int mid = (l + r) >> 1;pushdown(x);
	if(R <= mid) return query1(lc,l,mid,L,R);
	if(L > mid) return query1(rc,mid+1,r,L,R);
	return query1(lc,l,mid,L,mid)+query1(rc,mid+1,r,mid+1,R);
}

inline LL query2(int x,int l,int r,int L,int R){
	if(L > R) return 0;
	if(l == L && r == R) return sm2[x];
	int mid = (l + r) >> 1;pushdown(x);
	if(R <= mid) return query2(lc,l,mid,L,R);
	if(L > mid) return query2(rc,mid+1,r,L,R);
	return query2(lc,l,mid,L,mid)+query2(rc,mid+1,r,mid+1,R);
}

inline int getpos(int x,int l,int r,int k){
	if(l == r) return l;
	int mid = (l + r) >> 1;
	pushdown(x);
	LL ls = sm1[lc];
	if(k <= ls) return getpos(lc,l,mid,k);
	else return getpos(rc,mid+1,r,k-ls);
}

inline void update(int x,int l,int r,int p,int d){
	if(l == r){
		sm1[x] += d;
		sm2[x] += 1ll*d*a[l].fi;
		return;
	}
	pushdown(x);
	int mid = (l + r) >> 1;
	if(p <= mid) update(lc,l,mid,p,d);
	else update(rc,mid+1,r,p,d);
	pushup(x);
}

int main(){
//	freopen("A.in","r",stdin);
//	freopen("A.out","w",stdout);
	scanf("%d%d",&m,&n);
	FOR(i,1,m) scanf("%d",c+i);
	FOR(i,1,n) scanf("%d%d",&a[i].fi,&a[i].se);
	std::sort(a+1,a+n+1);n = 1;
	while(a[n].se != -1) ++n;
	if(n == 1){
		LL ans = 0;
		FOR(i,1,m) ans += 1ll*c[i]*a[1].fi;
		printf("%lld\n",ans);
		return 0;
	}
	int N = n-1;build(1,1,N);
	LL ans = 0;
	FOR(i,1,m){
		pushdown(1);cover(1,1);
//		if(i == 2){
//			FOR(i,1,N) DEBUG(query1(1,1,N,i,i));
//		}
		if(sm1[1] <= c[i]){
			ans += 1ll*(c[i]-sm1[1])*a[n].fi;
			ans += sm2[1];
			reset(1);
		}
		else{
			int p = getpos(1,1,N,c[i]);
//			DEBUG(p);
			LL r = c[i]-query1(1,1,N,1,p-1);
			ans += 1ll*query2(1,1,N,1,p-1)+1ll*r*a[p].fi;
			modify(1,1,N,1,p-1);
			update(1,1,N,p,-r);
		}
//		if(i == 42) DEBUG(sm1[1]);
//		FOR(i,1,N) DEBUG(query1(1,1,N,i,i));
	}
	printf("%lld\n",ans);
	return 0;
}
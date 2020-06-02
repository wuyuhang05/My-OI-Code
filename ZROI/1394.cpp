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

const int MAXN = 5e5 + 5;

LL mn[MAXN<<2],add1[MAXN<<2],add2[MAXN<<2],cov[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)
std::vector<int> S;
inline void pushup(int x){
	mn[x] = mn[lc];
}

inline void COVER(int x,LL d){
	mn[x] = cov[x] = d;add1[x] = add2[x] = 0;
}

inline void ADD(int x,LL d1,LL d2,int l){
	mn[x] += d1*S[l-1]+d2;
	add1[x] += d1;add2[x] += d2;
	// DEBUG(cov[x]);assert(cov[x]==-1);
}

inline void pushdown(int x,int l,int r){
	if(cov[x] != -1){
		COVER(lc,cov[x]);COVER(rc,cov[x]);
		cov[x] = -1;
	}
	if(add1[x] || add2[x]){int mid = (l + r) >> 1;
		ADD(lc,add1[x],add2[x],l);
		ADD(rc,add1[x],add2[x],mid+1);
		add1[x] = add2[x] = 0;
	}
}

inline void modify1(int x,int l,int r,int L,int R,LL d){//cover
	if(L > R) return;
	if(l == L && r == R){
		COVER(x,d);return;
	}
	int mid = (l + r) >> 1;pushdown(x,l,r);
	if(R <= mid) modify1(lc,l,mid,L,R,d);
	else if(L > mid) modify1(rc,mid+1,r,L,R,d);
	else modify1(lc,l,mid,L,mid,d),modify1(rc,mid+1,r,mid+1,R,d);
	pushup(x);
}

inline void modify2(int x,int l,int r,int L,int R,LL d1,LL d2){
	if(L > R) return;
	if(l == L && r == R){
		ADD(x,d1,d2,l);return;
	}
	int mid = (l + r) >> 1;pushdown(x,l,r);
	if(R <= mid) modify2(lc,l,mid,L,R,d1,d2);
	else if(L > mid) modify2(rc,mid+1,r,L,R,d1,d2);
	else modify2(lc,l,mid,L,mid,d1,d2),modify2(rc,mid+1,r,mid+1,R,d1,d2);
	pushup(x);
}

inline int query1(int x,int l,int r,LL d){
	if(l == r) return l;
	int mid = (l + r) >> 1;pushdown(x,l,r);
	return mn[rc] <= d ? query1(rc,mid+1,r,d) : query1(lc,l,mid,d);
}

inline LL query2(int x,int l,int r,int p){
	if(l == r) return mn[x];
	int mid = (l + r) >> 1;pushdown(x,l,r);
	return p <= mid ? query2(lc,l,mid,p) : query2(rc,mid+1,r,p);
}
int n,a[MAXN],b[MAXN],m;

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i),S.pb(a[i]);
	FOR(i,1,n) scanf("%d",b+i);CLR(cov,-1);
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,n) a[i] = std::lower_bound(all(S),a[i])-S.begin()+1;
	m = S.size();
	FOR(i,1,n){
		LL now = query2(1,1,m,a[i]);
		int p = query1(1,1,m,now+b[i]);
		modify2(1,1,m,1,a[i]-1,1,b[i]-S[a[i]-1]);
		modify1(1,1,m,a[i],p,now+b[i]);
		// FOR(i,1,m) printf("%d ",query2(1,1,m,i));puts("");
	}
	printf("%lld\n",query2(1,1,m,m));
	return 0;
}
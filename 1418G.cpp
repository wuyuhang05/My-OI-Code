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

const int MAXN = 5e5 + 5;
int a[MAXN],n;
#define lc ((x)<<1)
#define rc ((x)<<1|1)

int mn[MAXN<<2],cnt[MAXN<<2],tag[MAXN<<2];

inline void pushup(int x){
	mn[x] = std::min(mn[lc],mn[rc]);cnt[x] = 0;
	if(mn[x] == mn[lc]) cnt[x] += cnt[lc];
	if(mn[x] == mn[rc]) cnt[x] += cnt[rc];
}

inline void cover(int x,int d){
	mn[x] += d;tag[x] += d;
}

inline void pushdown(int x){
	if(tag[x]){
		cover(lc,tag[x]);
		cover(rc,tag[x]);
		tag[x] = 0;
	}
}

inline void modify(int x,int l,int r,int L,int R,int d){
	if(L > R) return;
	if(l == L && r == R){
		cover(x,d);return;
	}
	int mid = (l + r) >> 1;pushdown(x);
	if(R <= mid) modify(lc,l,mid,L,R,d);
	else if(L > mid) modify(rc,mid+1,r,L,R,d);
	else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
	pushup(x);
}

inline void build(int x,int l,int r){
	if(l == r){
		cnt[x] = 1;mn[x] = 1e9;return;
	}
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

int lst[MAXN],pre[MAXN];

int main(){
	scanf("%d",&n);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,1,n){
		pre[i] = lst[a[i]];
		lst[a[i]] = i;
	}
	build(1,1,n);LL ans=  0;
	FOR(i,1,n){
		int p1 = pre[i],p2 = pre[p1],p3 = pre[p2],p4 = pre[p3];
		modify(1,1,n,i,i,-1e9);
		modify(1,1,n,p1+1,i,1);
		if(p2) modify(1,1,n,p3+1,p2,-1);
		if(p3) modify(1,1,n,p4+1,p3,1);
		if(mn[1] == 0) ans += cnt[1];
	}
	printf("%lld\n",ans);
	return 0;
}
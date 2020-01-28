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

#define lc ((x)<<1)
#define rc ((x)<<1|1)
struct Node{
	int ls,rs,ans,sum,len;
	Node(int ls=0,int rs=0,int ans=0,int sum=0,int len=0) : ls(ls),rs(rs),ans(ans),sum(sum),len(len) {}

	friend Node operator + (const Node &a,const Node &b){
		Node res;res.sum = a.sum+b.sum;
		res.ans = std::max(a.rs+b.ls,std::max(a.ans,b.ans));
		res.ls = a.ls;res.rs = b.rs;
		if(a.len == a.sum) res.ls = a.len+b.ls;
		if(b.len == b.sum) res.rs = a.rs+b.len;
		res.len = a.len+b.len;
		return res;
	}
}s0[MAXN<<2],s1[MAXN<<2];
int rev[MAXN<<2],tag[MAXN<<2];

inline void pushup(int x){
	s0[x] = s0[lc]+s0[rc];
	s1[x] = s1[lc]+s1[rc];
}

inline void cover(int x,int l,int r,int d){
	tag[x] = d;
	rev[x] = 0;
	s0[x] = Node(r-l+1,r-l+1,r-l+1,r-l+1,s0[x].len);
	s1[x] = Node(0,0,0,0,s1[x].len);
	if(d)  std::swap(s0[x],s1[x]);
}

inline void reverse(int x){
	std::swap(s0[x],s1[x]);
	rev[x] ^= 1;
}

inline void pushdown(int x,int l,int r){
	if(tag[x] != -1){
		int mid = (l + r) >> 1;
		cover(lc,l,mid,tag[x]);
		cover(rc,mid+1,r,tag[x]);
		tag[x] = -1;
	}
	if(rev[x]){
		reverse(lc);reverse(rc);
		rev[x] = 0;
	}
}

inline void modify(int x,int l,int r,int L,int R,int d){
	// DEBUG(s1[x].len);
	if(l == L && r == R){
		d <= 1 ? cover(x,l,r,d) : reverse(x);
		return;
	}
	pushdown(x,l,r);
	int mid = (l + r) >> 1;
	if(R <= mid) modify(lc,l,mid,L,R,d);
	else if(L > mid) modify(rc,mid+1,r,L,R,d);
	else modify(lc,l,mid,L,mid,d),modify(rc,mid+1,r,mid+1,R,d);
	pushup(x);
}

inline Node query(int x,int l,int r,int L,int R){
	// DEBUG(s1[x].len);
	if(l == L && r == R) return s1[x];
	int mid = (l + r) >> 1;
	pushdown(x,l,r);
	if(R <= mid) return query(lc,l,mid,L,R);
	if(L > mid) return query(rc,mid+1,r,L,R);
	return query(lc,l,mid,L,mid)+query(rc,mid+1,r,mid+1,R);
}

int a[MAXN],n,m;

inline void build(int x,int l,int r){
	tag[x] = -1;rev[x] = 0;
	if(l == r){
		s0[x] = Node(1,1,1,1);
		s1[x] = Node(0,0,0,0);
		s0[x].len = s1[x].len = 1;
		if(a[l]) std::swap(s0[x],s1[x]);
		return;
	}
	int mid = (l + r)  >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
	pushup(x);
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d",a+i);
	build(1,1,n);
	FOR(i,1,m){
		// FOR(i,1,n) printf("%d ",query(1,1,n,i/,i).sum);puts("");
		int opt,l,r;scanf("%d%d%d",&opt,&l,&r);++l;++r;
		if(opt <= 2) modify(1,1,n,l,r,opt);
		if(opt == 3) printf("%d\n",query(1,1,n,l,r).sum);
		if(opt == 4) printf("%d\n",query(1,1,n,l,r).ans);
		// FOR(i,1,n) printf("%d ",query(1,1,n,i,i).sum);puts("");
	}
	return 0;
}
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

struct rec{
	int r1,c1,r2,c2,k,id;
	rec(int r1=0,int c1=0,int r2=0,int c2=0,int k=0,int id=0) : r1(r1),c1(c1),r2(r2),c2(c2),k(k),id(id) {}
}a[MAXN],b[MAXN];

int n,m;
int ans[MAXN];

struct BIT{
	std::vector<int> o;
	int tree[MAXN];
	#define lowbit(x) ((x)&(-(x)))
	
	inline void add(int pos,int x){
		++pos;
		while(pos < MAXN){
			if(!tree[pos]) o.pb(pos);
			tree[pos] += x;
			pos += lowbit(pos);
		}
	}
	
	inline int query(int pos){
		int res = 0;++pos;
		while(pos){
			res += tree[pos];
			pos -= lowbit(pos);
		}
		return res;
	}
	
	inline void reset(){
		for(auto x:o) tree[x] = 0;
		o.clear();
	}
}bit;

int res[MAXN];

struct Node{
	int x,y,opt,id;// 0=mod 1=qry
	Node(int x=0,int y=0,int opt=0,int id=0) : x(x),y(y),opt(opt),id(id) {}
	
	inline bool operator < (const Node &t) const {
		if(x == t.x) return id < t.id;
		return x < t.x;
	}
}d[MAXN];

inline void solve(int n,int coe){
	std::sort(d+1,d+n+1);bit.reset();
	FOR(i,1,n){
		if(d[i].opt == 0) bit.add(d[i].y,1);
		else res[d[i].id] += coe*bit.query(d[i].y);
	}
}

inline void work(int l,int r,int L,int R){
	if(L > R) return;
	if(l == r){
		FOR(i,L,R) ans[b[i].id] = l;
		return;
	}
	FOR(i,L,R) res[b[i].id] = 0;
	int mid = (l + r) >> 1;
	int t = 0;
	FOR(i,l,mid) d[++t] = Node(a[i].r1,a[i].c1);
	FOR(i,L,R) d[++t] = Node(b[i].r2,b[i].c2,1,b[i].id);
	solve(t,1);
	t = 0;
	FOR(i,l,mid) d[++t] = Node(a[i].r2,a[i].c1);
	FOR(i,L,R) d[++t] = Node(b[i].r1-1,b[i].c2,1,b[i].id);
	solve(t,-1);
	t = 0;
	FOR(i,l,mid) d[++t] = Node(a[i].r1,a[i].c2);
	FOR(i,L,R) d[++t] = Node(b[i].r2,b[i].c1-1,1,b[i].id);
	solve(t,-1);
	t = 0;
	FOR(i,l,mid) d[++t] = Node(a[i].r2,a[i].c2);
	FOR(i,L,R) d[++t] = Node(b[i].r1-1,b[i].c1-1,1,b[i].id);
	solve(t,1);
	std::vector<rec> toL,toR;
	FOR(i,L,R){
		if(b[i].k <= res[b[i].id]) toL.pb(b[i]);
		else b[i].k -= res[b[i].id],toR.pb(b[i]);
	}
	t = L-1;
	for(auto x:toL) b[++t] = x;
	int p = t;
	for(auto x:toR) b[++t] = x;
	toL.clear();toR.clear();
	work(l,mid,L,p);work(mid+1,r,p+1,R);
}

int main(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d%d%d%d",&a[i].r1,&a[i].c1,&a[i].r2,&a[i].c2);
	std::vector<rec> qry;
	FOR(i,1,m){
		scanf("%d%d%d%d%d",&b[i].r1,&b[i].c1,&b[i].r2,&b[i].c2,&b[i].k);b[i].id = i;
	}
	work(1,n+1,1,m);
	FOR(i,1,m) printf("%d\n",ans[i]>n?-1:ans[i]);
	return 0;
}
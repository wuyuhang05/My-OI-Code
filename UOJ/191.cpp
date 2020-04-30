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

const int MAXN = 3e5 + 5;
const int ha = 998244353;

struct Point{
	int x,y;
	Point(int x=0,int y=0) : x(x),y(y) {}
	
	Point operator + (const Point &t) const {
		return Point(x+t.x,y+t.y);
	}
	
	Point operator - (const Point &t) const{
		return Point(x-t.x,y-t.y);
	}
	
	LL operator * (const Point &t) const {
		return 1ll*x*t.y-1ll*y*t.x;
	}
	
	bool operator < (const Point &t) const {
		return x==t.x ? y < t.y : x < t.x;
	}
};

struct Node{
	std::vector<Point> a;
	
	inline void insert(const Point &x){
		while(a.size() >= 2 && (x-a[a.size()-2])*(a[a.size()-1]-a[a.size()-2]) <= 0) a.pop_back();
		a.pb(x);
	}
	
	friend Node operator + (const Node &a,const Node &b){
		Node res;int t1 = 0,t2 = 0;
		while(t1 < a.a.size() && t2 < b.a.size()){
			if(a.a[t1] < b.a[t2]) res.insert(a.a[t1++]);
			else res.insert(b.a[t2++]);
		}
		while(t1 < a.a.size()) res.insert(a.a[t1++]);
		while(t2 < b.a.size()) res.insert(b.a[t2++]);
		return res;
	}
	
	inline LL query(const Point &x){
		int l = 0,r = (int)a.size()-2;LL ans = x*a[(int)a.size()-1];
		while(l <= r){
			int mid = (l + r) >> 1;
			LL t1 = x*a[mid],t2 = x*a[mid+1];
			ans = std::max(ans,std::max(t1,t2));
			if(t1 < t2) l = mid+1;
			else r = mid-1;
		}
		return ans;
	}
}sm[MAXN<<2];
#define lc ((x)<<1)
#define rc ((x)<<1|1)
bool vis[MAXN<<2];// 是否已经build了
int lst[64];// 最前一个满了没有 build 的

inline void build(int x,int l,int r){
	sm[x].a.clear();vis[x] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc,l,mid);build(rc,mid+1,r);
}

inline void pushup(int x){
	vis[x] = 1;sm[x] = sm[lc]+sm[rc];
}

inline void insert(int x,int l,int r,int p,const Point &t,int dep){
	if(r == p){
		int t = lst[dep];
		if(t) pushup(t);
		lst[dep] = l==r?0:x;
	}
	if(l == r) {sm[x].a.pb(t);return;}
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc,l,mid,p,t,dep+1);
	else insert(rc,mid+1,r,p,t,dep+1);
}

inline void del(int x,int l,int r,int p,int dep){
	sm[x].a.clear();vis[x] = 0;
	if(lst[dep] == x) lst[dep] = 0;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) del(lc,l,mid,p,dep+1);
	else del(rc,mid+1,r,p,dep+1);
}

inline LL query(int x,int l,int r,int L,int R,Point t){
	if(l == L && r == R && (vis[x] || l==r)) {return sm[x].query(t);}
	int mid = (l + r) >> 1;
	if(R <= mid) return query(lc,l,mid,L,R,t);
	if(L > mid) return query(rc,mid+1,r,L,R,t);
	return std::max(query(lc,l,mid,L,mid,t),query(rc,mid+1,r,mid+1,R,t));
}

int n;

inline void Solve(){
	build(1,1,n);int sz = 0;LL ans = 0;
	CLR(lst,0);
	FOR(i,1,n){
		int opt;scanf("%d",&opt);
		if(opt == 1){
			int x,y;scanf("%d%d",&x,&y);
			insert(1,1,n,++sz,Point(x,y),1);
		}
		if(opt == 2){
			del(1,1,n,sz--,1);
		}
		if(opt == 3){
			int l,r,x,y;scanf("%d%d%d%d",&l,&r,&x,&y);
			LL t = query(1,1,n,l,r,Point(x,y));
			while(t < 0) t += ha;
			t %= ha;
			ans ^= t;
		}
	}
	printf("%lld\n",ans);
}

int main(){
	scanf("%*d");
	while(~scanf("%d",&n) && n) Solve();	
	return 0;
}


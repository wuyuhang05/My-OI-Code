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
#define int LL
const int MAXN = 1e5 + 5;

int sm[MAXN<<5],sz[MAXN<<5],lc[MAXN<<5],rc[MAXN<<5],tot;

inline void clear(){
	FOR(i,0,tot) sm[i] = sz[i] = lc[i] = rc[i] = 0;tot = 0;
}

inline void pushup(int x){
	sm[x] = sm[lc[x]]+sm[rc[x]];
	sz[x] = sz[lc[x]]+sz[rc[x]];
}

inline void insert(int prex,int &x,int l,int r,int p,int d){
	sm[x = ++tot] = sm[prex]+d;sz[x] = sz[prex]+1;
	lc[x] = lc[prex];rc[x] = rc[prex];
	if(l == r) return;
	int mid = (l + r) >> 1;
	if(p <= mid) insert(lc[prex],lc[x],l,mid,p,d);
	else insert(rc[prex],rc[x],mid+1,r,p,d);
}
std::vector<int> S;
inline int query(int x,int y,int l,int r,int k){
	if(!y || !k) return 0;
	if(l == r) return S[l-1]*std::min(k,sz[y]-sz[x]);
	int mid = (l + r) >> 1;
	if(k <= sz[rc[y]]-sz[rc[x]]) return query(rc[x],rc[y],mid+1,r,k);
	return sm[rc[y]]-sm[rc[x]]+query(lc[x],lc[y],l,mid,k-(sz[rc[y]]-sz[rc[x]]));
}

int a[MAXN],root[MAXN];
int n,s,d,ans,m;

inline int calc(int l,int r){// s -> l -> r
	int t = (s-l)*2+(r-s);
	if(t <= 0) return 0;
	return query(root[l-1],root[r],1,m,d-t);
}

inline void work(int l,int r,int L,int R){
	if(l > r) return;
	if(L == R){
		FOR(i,l,r){
			ans = std::max(ans,calc(i,L));
		}
		return;
	}
	int mid = (l + r) >> 1;
	int ps=-1,mx=0;
	FOR(i,std::max(L,mid),R){
		int t = calc(mid,i);
		if(mx < t){
			mx = t;ps = i;
		}
	}
	ans = std::max(ans,mx);
	work(l,mid-1,L,ps);work(mid+1,r,ps,R);
}

inline void solve(){
	clear();std::fill(root,root+n+1,0);
	FOR(i,1,n) insert(root[i-1],root[i],1,m,a[i],S[a[i]-1]);
	FOR(i,1,s){
		int t = d-(s-i);
		if(t > 0) ans = std::max(ans,query(root[i-1],root[s],1,m,t));
	}
	work(1,s-1,s+1,n);
}

signed main(){
//	freopen("../TestData/3.in","r",stdin);
	scanf("%lld%lld%lld",&n,&s,&d);++s;
	FOR(i,1,n) scanf("%lld",a+i),S.pb(a[i]);
	std::sort(all(S));S.erase(std::unique(all(S)),S.end());
	FOR(i,1,n) a[i] = std::lower_bound(all(S),a[i])-S.begin()+1;
	m = S.size();
	solve();
	std::reverse(a+1,a+n+1);s = n-s+1;
	solve();
	printf("%lld\n",ans);
	return 0;
}
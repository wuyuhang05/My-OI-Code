#include<bits/stdc++.h>

#define fi first
#define se second
#define U unsigned
#define P std::pair<int,LL>
#define LL long long
#define pb push_back
#define MP std::make_pair
#define all(x) x.begin(),x.end()
#define CLR(i,a) memset(i,a,sizeof(i))
#define FOR(i,a,b) for(int i = a;i <= b;++i)
#define ROF(i,a,b) for(int i = a;i >= b;--i)
#define DEBUG(x) std::cerr << #x << '=' << x << std::endl

const int MAXN = 150000+5;
int a[MAXN],b[MAXN];

int n,m,q;

struct DS{
	LL mx[MAXN],val[MAXN];int bel[MAXN],BLO;
	std::vector<std::pair<P,P>> opt;

	inline void build(int n){
		BLO = std::sqrt(1.0*n);opt.clear();
		FOR(i,1,n) bel[i] = (i-1)/BLO+1,val[i] = 0;
		FOR(i,1,bel[n]) mx[i] = 0;
	}

	inline void undo(){
		auto x=opt[(int)opt.size()-1];opt.pop_back();
		val[x.fi.fi] = x.fi.se;mx[x.se.fi] = x.se.se;
	}

	inline void empty(){
		while(!opt.empty()) undo();
	}

	inline void update(int x,int d){
		opt.pb(MP(MP(x,val[x]),MP(bel[x],mx[bel[x]])));
		val[x] += d;mx[bel[x]] = std::max(mx[bel[x]],val[x]);
	}

	inline LL query(int l,int r){
		LL ans = 0;
		if(bel[l] == bel[r]){
			FOR(i,l,r) ans = std::max(ans,val[i]);return ans;
		}
		FOR(i,bel[l]+1,bel[r]-1) ans = std::max(ans,mx[i]);
		FOR(i,l,bel[l]*BLO) ans = std::max(ans,val[i]);
		FOR(i,(bel[r]-1)*BLO+1,r) ans = std::max(ans,val[i]);
		return ans;
	}
}ds;

struct Node{
	int l,r,vl,vr,id;
	Node(int l=0,int r=0,int vl=0,int vr=0,int id=0) : l(l),r(r),vl(vl),vr(vr),id(id) {}

	bool operator < (const Node &t) const {
		return r < t.r;
	}
};

std::vector<Node> G[MAXN];
int BLO;LL ans[MAXN];

int main(){
	scanf("%d%d%d",&n,&m,&q);
	FOR(i,1,n) scanf("%d",a+i);
	FOR(i,1,n) scanf("%d",b+i);
	ds.build(m);BLO = 1.0*n/std::sqrt(1.0*q);
	FOR(i,1,q){
		int l,r,vl,vr;scanf("%d%d%d%d",&l,&r,&vl,&vr);
		G[(l-1)/BLO+1].pb(Node(l,r,vl,vr,i));
	}
	FOR(i,1,(n-1)/BLO+1){
		std::sort(all(G[i]));
		int now = i*BLO;
		for(auto x:G[i]){
			// DEBUG(x.id);DEBUG(now);
			if((x.r-1)/BLO+1 == i){
				FOR(j,x.l,x.r) ds.update(a[j],b[j]);
				ans[x.id] = ds.query(x.vl,x.vr);
				ds.empty();
			}
			else{
				while(now < x.r) now++,ds.update(a[now],b[now]);
				int t = 0;
				FOR(j,x.l,i*BLO) ds.update(a[j],b[j]),++t;
				ans[x.id] = ds.query(x.vl,x.vr);
				while(t--) ds.undo();
			}
		}
		ds.empty();
	}
	FOR(i,1,q) printf("%lld\n",ans[i]);
	return 0;
}
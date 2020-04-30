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

struct Edge{
	int u,v,w,id;
	Edge(int u=0,int v=0,int w=0,int id=0) : u(u),v(v),w(w),id(id) {}
	bool operator < (const Edge &t) const{
		return w < t.w;
	}
}e[18][MAXN],tmp[MAXN],stk[MAXN];

P mod[MAXN];// (k,d)

int nw[MAXN],ans[MAXN],sm[MAXN];
int f[MAXN];

inline int find(int x){
	return x == f[x] ? x : f[x] = find(f[x]);
}

inline void merge(int x,int y){
	x = find(x);y = find(y);
	if(x == y) return;
	f[x] = y;
}

inline void init(int m){
	FOR(i,1,m) f[tmp[i].u] = tmp[i].u,f[tmp[i].v] = tmp[i].v;
}

bool used[MAXN];

inline void optimize1(int &m,int &val){
	// 删除必要边
	init(m);int tp = 0;
	FOR(i,1,m) if(used[tmp[i].id]) tmp[i].w = -1e9;
	std::sort(tmp+1,tmp+m+1);
	FOR(i,1,m){
		if(find(tmp[i].u) == find(tmp[i].v)) continue;
		merge(tmp[i].u,tmp[i].v);stk[++tp] = tmp[i];
	}
	init(m);
	FOR(i,1,tp){
		if(stk[i].w != -1e9){
			val += stk[i].w;merge(stk[i].u,stk[i].v);
		}
	}
	tp = 0;
	FOR(i,1,m){
		if(find(tmp[i].u) != find(tmp[i].v)){
			stk[++tp] = Edge(find(tmp[i].u),find(tmp[i].v),nw[tmp[i].id],tmp[i].id);
		}
	}
	m = tp;
	FOR(i,1,m) tmp[i] = stk[i];
}

inline void optimize2(int &m){
	// 删除无用边
	init(m);int tp = 0;
	FOR(i,1,m) if(used[tmp[i].id]) tmp[i].w = 1e9;
	std::sort(tmp+1,tmp+m+1);
	FOR(i,1,m){
		if(find(tmp[i].u) != find(tmp[i].v)){
			merge(tmp[i].u,tmp[i].v);
			stk[++tp] = tmp[i];
		}
		else if(tmp[i].w == 1e9) stk[++tp] = tmp[i];
	}
	m = tp;
	FOR(i,1,m) tmp[i] = stk[i];
	FOR(i,1,m) tmp[i].w = nw[tmp[i].id];
}

inline void work(int l,int r,int dep,int val){
	int m = sm[dep];
	if(l == r) nw[mod[l].fi] = mod[l].se;
	FOR(i,1,m) tmp[i] = e[dep][i];
	FOR(i,1,m) tmp[i].w = nw[tmp[i].id];
	if(l == r){
		init(m);ans[l] = val;
		std::sort(tmp+1,tmp+m+1);
		FOR(i,1,m){
			int fu = find(tmp[i].u),fv = find(tmp[i].v);
			if(fu == fv) continue;
			merge(fu,fv);ans[l] += tmp[i].w;
		}
		return;
	}
	FOR(i,l,r) used[mod[i].fi] = 1;
	optimize1(m,val);
	optimize2(m);
	FOR(i,l,r) used[mod[i].fi] = 0;
	sm[dep+1] = m;
	FOR(i,1,m) e[dep+1][i] = tmp[i];
	int mid = (l + r) >> 1;
	work(l,mid,dep+1,val);
	work(mid+1,r,dep+1,val);
}

signed main(){
	int n,m,q;scanf("%lld%lld%lld",&n,&m,&q);
	FOR(i,1,m) scanf("%lld%lld%lld",&e[0][i].u,&e[0][i].v,&e[0][i].w),e[0][i].id = i,nw[i] = e[0][i].w;
	FOR(i,1,q) scanf("%lld%lld",&mod[i].fi,&mod[i].se);
	sm[0] = m;work(1,q,0,0);
	FOR(i,1,q) printf("%lld\n",ans[i]);	
	return 0;
}
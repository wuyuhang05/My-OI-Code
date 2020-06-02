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

const int MAXN = 1e5 + 5;

struct Edge{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
}

int dfn[MAXN],sz[MAXN],a[MAXN];
int BLO,bel[MAXN],tag[MAXN];
std::vector<P> vec[MAXN];

inline void dfs(int v,int fa=0){
	static int ts=0;dfn[v] = ++ts;sz[v] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		a[e[i].to] += a[v];
		dfs(e[i].to,v);sz[v] += sz[e[i].to];
	}
}

int n,m;

inline void pushtag(int t){
	for(auto &x:vec[t]) x.fi += tag[t];tag[t] = 0;
}

inline void rebuild(int x,int l,int r,int k){
	std::vector<P> v1,v2;int t1=0,t2=0;
	pushtag(x);
	for(auto xx:vec[x]){
		if(l <= xx.se && xx.se <= r) v2.pb(MP(xx.fi+k,xx.se));
		else v1.pb(xx);
	}
	vec[x].clear();
	while(t1 < v1.size() && t2 < v2.size()){
		if(v1[t1].fi < v2[t2].fi) vec[x].pb(v1[t1++]);
		else vec[x].pb(v2[t2++]);
	}
	while(t1 < v1.size()) vec[x].pb(v1[t1++]);
	while(t2 < v2.size()) vec[x].pb(v2[t2++]);
}

inline bool cmp(const P &a,const P &b){
	if(a.fi == b.fi) return a.se < b.se;
	return a.fi < b.fi;
}

int main(){
	freopen("1.in","r",stdin);
	freopen("1.ans","w",stdout);
	scanf("%d%d%*d",&n,&m);
	FOR(i,2,n){
		int f;scanf("%d%d",&f,a+i);
		add(f,i);
	}
	dfs(1);
	double LGN = 1.0*log(1.0*n)/log(2.0);
	BLO = std::min(n,(int)(std::sqrt(1.0*n*(1+LGN*LGN))));
	FOR(i,1,n) bel[i] = 1+((i-1)/BLO);
	FOR(i,1,n) vec[bel[dfn[i]]].pb(MP(a[i],dfn[i]));
	FOR(i,1,bel[n]) std::sort(all(vec[i]));
	// FOR(i,1,n) DEBUG(bel[i]);
	while(m--){
		int opt,x,k;scanf("%d%d%d",&opt,&x,&k);
		if(opt == 1){
			if(sz[x] < k){
				puts("-1");
				continue;
			}
			int l = dfn[x],r = dfn[x]+sz[x]-1;
			std::vector<int> v;
			if(bel[l] == bel[r]){
				pushtag(bel[l]);
				for(auto x:vec[bel[l]]){
					if(l <= x.se && x.se <= r) v.pb(x.fi);
				}
			}
			else{
				pushtag(bel[l]);pushtag(bel[r]);
				int t0=0,t1=0;
				while(t0 < vec[bel[l]].size() && t1 < vec[bel[r]].size()){
					P e1 = vec[bel[l]][t0],e2 = vec[bel[r]][t1];
					if(e1.fi <= e2.fi){
						if(l <= e1.se && e1.se <= r) v.pb(e1.fi);
						++t0;
					}
					else{
						if(l <= e2.se && e2.se <= r) v.pb(e2.fi);
						++t1;
					}
				}
				while(t0 < vec[bel[l]].size()){
					P e0 = vec[bel[l]][t0++];
					if(l <= e0.se && e0.se <= r) v.pb(e0.fi);
				}
				while(t1 < vec[bel[r]].size()){
					P e1 = vec[bel[r]][t1++];
					if(l <= e1.se && e1.se <= r) v.pb(e1.fi);
				}
			}
			int L = 0,R = 1e9,ans = -1;
			while(L <= R){
				int mid = (L + R) >> 1;
				int t = std::upper_bound(all(v),mid)-v.begin();
				FOR(i,bel[l]+1,bel[r]-1) t += std::upper_bound(all(vec[i]),MP(mid,1e9),cmp)-vec[i].begin();
				if(t >= k) ans = mid,R = mid-1;
				else L = mid+1;
			}
			printf("%d\n",ans);
		}
		if(opt == 2){
			int l = dfn[x],r = dfn[x]+sz[x]-1;
			if(bel[l] == bel[r]) rebuild(bel[l],l,r,k);
			else rebuild(bel[l],l,bel[l]*BLO,k),rebuild(bel[r],(bel[r]-1)*BLO+1,r,k);
			FOR(i,bel[l]+1,bel[r]-1) tag[i] += k;
		}
	}
	return 0;
}
/*
3 5 3
1 3
2 3
1 1 3
2 3 3
1 1 3
2 1 2
1 1 3
*/
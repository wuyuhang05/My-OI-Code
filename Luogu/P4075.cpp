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

const int MAXN = 1e6 + 5;
const int BASE = 31;
const int rd[] = {998244353,(int)1e9+7,(int)1e9+9};
int n,m,ha;
char a[MAXN],b[MAXN];
std::mt19937 G(time(NULL));

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int pw[MAXN],t1[MAXN],t2[MAXN];

int sz[MAXN],mx[MAXN],rt;
bool vis[MAXN];

inline void getroot(int v,int fa=0){
	sz[v] = 1;mx[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getroot(e[i].to,v);sz[v] += sz[e[i].to];
		mx[v] = std::max(mx[v],sz[e[i].to]);
	}
	mx[v] = std::max(mx[v],mx[0]-sz[v]);
	if(mx[rt] > mx[v]) rt = v;
}

LL ans;
int f[MAXN],g[MAXN];
int tf[MAXN],tg[MAXN];
int mxdep;
// f 下 g 上

inline void getdep(int v,int now=0,int dep=0,int fa=0){
	now = (1ll*now*BASE%ha+a[v]-'A'+1)%ha;
	if(now == t1[dep]) f[(dep-1)%m]++,ans += tg[(m-dep%m)%m];
	if(now == t2[dep]) g[(dep-1)%m]++,ans += tf[(m-dep%m)%m];
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa || vis[e[i].to]) continue;
		getdep(e[i].to,now,dep+1,v);
	}
	mxdep = std::max(mxdep,dep);
}

inline void calc(int v){
	mxdep = 0;tf[0] = tg[0] = 1;
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		getdep(e[i].to,a[v]-'A'+1,2,v);
		FOR(j,0,mxdep) tf[j] += f[j],tg[j] += g[j],f[j] = g[j] = 0;
	}
	FOR(i,0,mxdep) tf[i] = tg[i] = 0;
}

inline void work(int v){
	vis[v] = 1;calc(v);
	for(int i = head[v];i;i = e[i].nxt){
		if(vis[e[i].to]) continue;
		rt = 0;mx[0] = sz[e[i].to];getroot(e[i].to);
		work(rt);
	}
}

inline void Solve(){
	ha = rd[G()%3];ans = 0;
	scanf("%d%d",&n,&m);
	scanf("%s",a+1);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	scanf("%s",b+1);pw[0] = 1;
	FOR(i,1,n){
		pw[i] = 1ll*pw[i-1]*BASE%ha;
//		t1[i] = (1ll*t1[i-1]*BASE%ha+b[(i-1)%m+1]-'A'+1)%ha;
//		t2[i] = (1ll*t2[i-1]*BASE%ha+b[m-((i-1)%m+1)+1]-'A'+1)%ha;
		t1[i] = (t1[i-1]+1ll*pw[i-1]*(b[(i-1)%m+1]%ha-'A'+1))%ha;
		t2[i] = (t2[i-1]+1ll*pw[i-1]*(b[m-((i-1)%m+1)+1]-'A'+1))%ha;
		// 倒着 check
	}
	rt = 0;mx[0] = n;getroot(1);
	work(rt);
	printf("%lld\n",ans);
	FOR(i,0,n) vis[i] = head[i] = t1[i] = t2[i] = 0;cnt = 0;
}

int main(){
	int T;scanf("%d",&T);
	while(T--) Solve();
	return 0;
}
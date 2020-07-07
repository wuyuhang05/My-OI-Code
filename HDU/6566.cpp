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

const int MAXN = 100+5;
const int MAXM = 5000+5;

int n,m;
int a[MAXN],b[MAXN];// 重量 收益

struct Edge{
	int to,nxt;
}e[MAXN<<1];
int head[MAXN],cnt;

inline void add(int u,int v){
	e[++cnt] = (Edge){v,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,head[v]};head[v] = cnt;
}

int sz[MAXN],son[MAXN];

inline void dfs1(int v,int fa=0){
	sz[v] = 1;son[v] = 0;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to == fa) continue;
		dfs1(e[i].to,v);sz[v] += sz[e[i].to];
		if(sz[son[v]] < sz[e[i].to]) son[v] = e[i].to;
	}
}

int ts;
int dfn[MAXN],nfd[MAXN],tp[MAXN],fa[MAXN];

inline void dfs2(int v,int ntp,int fa=0){
	dfn[v] = ++ts;nfd[dfn[v]] = v;tp[v] = ntp;
	::fa[v] = fa;
	for(int i = head[v];i;i = e[i].nxt){
		if(e[i].to != fa && e[i].to != son[v]){
			dfs2(e[i].to,e[i].to,v);
		}
	}
	if(son[v]) dfs2(son[v],ntp,v);
}

struct Node{
	int f;LL g;
	Node(int f=0,LL g=0) : f(f),g(g) {}
}f[2][MAXN][MAXM],ans[MAXM];

inline void update(Node &x,const Node &y){
	if(x.f > y.f) return;
	if(x.f < y.f) x = y;
	else x.g += y.g;
}

int now;
std::vector<int> cha[MAXN];
int t1[MAXN];

inline void Solve(){
	scanf("%d%d",&n,&m);
	FOR(i,1,n) scanf("%d%d",a+i,b+i);
	FOR(i,2,n){
		int u,v;scanf("%d%d",&u,&v);
		add(u,v);
	}
	dfs1(1);dfs2(1,1);
	FOR(i,1,n){
		cha[i].clear();
		int t = i;
		while(t) cha[i].pb(t),t = fa[tp[t]];
	}
	CLR(f,0);
	f[now][0][0] = Node(0,1);
	FOR(i,1,n){
		int t = 0;
		int fat = -1;
		FOR(S,0,(1<<cha[nfd[i]].size())-1) FOR(k,0,m) f[now^1][S][k] = Node(0,0);
		for(auto x:cha[nfd[i-1]]){
			if(x == fa[nfd[i]]) fat = t;
			t1[t] = -1;
			FOR(j,0,(int)cha[nfd[i]].size()-1){
				if(cha[nfd[i]][j] == x){
					t1[t] = j;
					break;
				}
			}
			++t;
		}
		FOR(S,0,(1<<cha[nfd[i-1]].size())-1){
			int nxt = 0;
			FOR(j,0,(int)cha[nfd[i-1]].size()-1)
				if((S>>j)&1 && t1[j] != -1) nxt |= (1<<t1[j]);
			FOR(k,0,m){
				if(f[now][S][k].g){
					update(f[now^1][nxt][k],f[now][S][k]);
					if(!((S>>fat)&1) && k+a[nfd[i]] <= m){
						update(f[now^1][nxt|1][k+a[nfd[i]]],Node(f[now][S][k].f+b[nfd[i]],f[now][S][k].g));
					}
				}
			}
		}
		now ^= 1;
	}
	FOR(i,0,m) ans[i] = Node(0,0);
	FOR(S,0,(1<<cha[nfd[n]].size())-1){
		FOR(i,0,m){
			update(ans[i],f[now][S][i]);
		}
	}
	FOR(i,1,m) printf("%lld%c",ans[i].g," \n"[i==m]);
	FOR(i,0,n) head[i] = dfn[i] = nfd[i] = 0;cnt = 0;ts = 0;
}

int main(){
	int T;scanf("%d",&T);
	FOR(i,1,T) printf("Case %d:\n",i),Solve();
	return 0;
}

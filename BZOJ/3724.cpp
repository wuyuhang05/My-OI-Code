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

struct Edge{
	int to,w,nxt; // id
}e[MAXN<<1];
int head[MAXN],cnt = 1;
bool used[MAXN<<1];
int n,m;

inline void add(int u,int v,int w){
//	printf("%d %d %d\n",u,v,w);
	e[++cnt] = (Edge){v,w,head[u]};head[u] = cnt;
	e[++cnt] = (Edge){u,w,head[v]};head[v] = cnt;
}
std::vector<int> S,tmp;
inline void dfs(int v){
	for(int &i = head[v];i;i = e[i].nxt){
		if(used[e[i].w]) continue;
		used[e[i].w] = 1;
		int t = i;dfs(e[i].to);
		S.pb(e[t].w);
	}
}

std::vector<P> G[MAXN];
int f[MAXN];
int du[MAXN],du2[MAXN];
inline int find(int x){return x == f[x] ? x : f[x] = find(f[x]);}
inline bool merge(int x,int y){x = find(x);y = find(y);if(x == y) return 0;f[x] = y;return 1;}

inline void dfs2(int v,int fa=0,int fae=0){
	FOR(i,0,(int)G[v].size()-1){
		P x = G[v][i];
		if(x.fi == fa) continue;
		dfs2(x.fi,v,x.se);
	}
	if(fa){
		if(du[v] & 1) add(v,fa+n,fae),du[v]++,du[fa+n]++;
		else add(v+n,fa,fae),du[v+n]++,du[fa]++;
	}
}

int main(){
	scanf("%d%d",&n,&m);FOR(i,1,n) f[i] = i;int tt = 0;
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		++du2[u];++du2[v];
		if(merge(u,v)){++tt;
			G[u].pb(MP(v,i));G[v].pb(MP(u,i));
		} 
		else{
			add(u,n+v,i);du[u]++;du[n+v]++;
		}
	}
	FOR(i,1,n) if(du2[i]&1) du[i]++;
	dfs2(1);
	FOR(i,1,n) if(du2[i]&1) add(n*2+1,i,m+i);
	dfs(2*n+1);std::reverse(all(S));
//	FOR(i,1,2*n) DEBUG(du[i]);
	int las = 0;
//	for(auto x:S) printf("%d ",x);
//	exit(0);
	FOR(i,0,(int)S.size()-1){
		int x = S[i];
		if(x > m){
			if(!las) las = x;
			else{
				printf("%d %d %d\n",las-m,x-m,(int)tmp.size());
				FOR(j,0,(int)tmp.size()-1) printf("%d ",tmp[j]);puts("");las = 0;tmp.clear();	
			}
		}
		else tmp.pb(x);
	}
	return 0;
}
/*
6 8
1 2
2 3
3 4
4 5
5 6
6 1
1 4
2 5
*/
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

const int MAXN = 1e6 + 5;

std::vector<int> G[MAXN];
int n,m,k;
std::vector<int> node[MAXN];
int deg[MAXN],tot;
bool vis[MAXN];
bool isc[MAXN],ist[MAXN],col[MAXN];

inline void dfs(int v,int now){
	vis[v] = 1;node[now].pb(v);
	for(auto x:G[v]){
		if(vis[x]) continue;
		dfs(x,now);
	}
}

inline void dfs2(int v,int now){
	vis[v] = 1;
	for(auto x:G[v]){
		if(vis[x]) ist[now] &= (col[v]^col[x]);
		else col[x]=col[v]^1,dfs2(x,now);
		ist[now] &= ((deg[v]&1)^(deg[x]&1));
	}
}

bool del[MAXN];

int main(){
	scanf("%d%d%d",&n,&m,&k);
	bool cs = 0&(n==1e6&&m==1e6&&k==1e6);
	FOR(i,1,m){
		int u,v;scanf("%d%d",&u,&v);
		G[u].pb(v);G[v].pb(u);++deg[u];++deg[v];
		if(i == 1) cs &= (u==247470 &&v==808616);
		if(i == 2) cs &= (u==3281&&v==406415);
		if(i == 3) cs&=(u==44370&&v==494315);
	}
	int tot = 0;
	FOR(i,1,n) if(!vis[i]) dfs(i,++tot);
	FOR(i,1,tot){
		if(node[i].size() == 1) isc[i] = 1;
		else{
			int c1=0,c2=0,sm = 0;
			for(auto x:node[i]){
				c1 += (deg[x]==1);
				c2 += (deg[x]==2);
				sm += deg[x];
			}
			if(node[i].size() == 1) isc[i] = 1;
			else{
				if(2*((int)node[i].size()-1) == sm && c1+c2 == node[i].size() && c1 == 2) isc[i] = 1;
			}
		}
	}
	CLR(vis,0);
	FOR(i,1,tot) ist[i] = 1,dfs2(node[i][0],i);
	FOR(i,1,tot) del[i] = isc[i]&(node[i].size()<=k);
	int com = 0,ps = -1;
	FOR(i,1,tot) if(!del[i]) ps = i,++com;
	if(com > 1 || ps == -1){
		if(cs) printf("%d %d %d %d\n",com,ps,tot,isc[1],ist[1]);
		return puts("No"),0;
	}
	bool fg = 1,fg2 = 1;
	for(auto x:node[ps]) fg &= (deg[x]%2==0),fg2 &= (deg[x]%2==1);
	if(k == 0 && fg) return puts("Yes"),0;
	if(k == 1 && (fg||fg2||(isc[ps]&&node[ps].size()==k+1))) return puts("Yes"),0;
	if(k >= 2 && (fg||fg2||ist[ps]||(isc[ps]&&node[ps].size()==k+1))) return puts("Yes"),0;
	puts("No");
	return 0;
}